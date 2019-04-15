# Ready modules
import os
from argparse import ArgumentParser
import sys

# Custom modules
sys.path.insert(0, 'src')
from optimize import optimize
from utils import save_img, get_img, exists, list_files


# Global default values
CONTENT_WEIGHT = 7.5e0
STYLE_WEIGHT = 1e2
TV_WEIGHT = 2e2
LEARNING_RATE = 1e-3
NUM_EPOCHS = 2
CHECKPOINT_DIR = 'checkpoints'
CHECKPOINT_ITERATIONS = 2000
BATCH_SIZE = 4
DEVICE = '/device:gpu:0'
FRAC_GPU = 1


def build_parser():
    """
        This function constructs input params parser.
        Returns:
            'parser' - ArgumentParser object
    """
    parser = ArgumentParser()
    parser.add_argument('--checkpoint-dir', type=str,
                        dest='checkpoint_dir', help='Dir to save checkpoint in',
                        metavar='CHECKPOINT_DIR', required=True)

    parser.add_argument('--style', type=str,
                        dest='style', help='Style image path',
                        metavar='STYLE', required=True)

    parser.add_argument('--train-path', type=str,
                        dest='train_path', help='Path to training images folder',
                        metavar='TRAIN_PATH', required=True)

    parser.add_argument('--epochs', type=int,
                        dest='epochs', help='Num of epochs',
                        metavar='EPOCHS', default=NUM_EPOCHS)

    parser.add_argument('--batch-size', type=int,
                        dest='batch_size', help='Batch size',
                        metavar='BATCH_SIZE', default=BATCH_SIZE)

    parser.add_argument('--checkpoint-iterations', type=int,
                        dest='checkpoint_iterations', help='Checkpoint frequency',
                        metavar='CHECKPOINT_ITERATIONS',
                        default=CHECKPOINT_ITERATIONS)

    parser.add_argument('--vgg-path', type=str,
                        dest='vgg_path',
                        help='Path to VGG19 network (default %(default)s)',
                        metavar='VGG_PATH', required=True)

    parser.add_argument('--content-weight', type=float,
                        dest='content_weight',
                        help='Content weight (default %(default)s)',
                        metavar='CONTENT_WEIGHT', default=CONTENT_WEIGHT)
    
    parser.add_argument('--style-weight', type=float,
                        dest='style_weight',
                        help='Style weight (default %(default)s)',
                        metavar='STYLE_WEIGHT', default=STYLE_WEIGHT)

    parser.add_argument('--tv-weight', type=float,
                        dest='tv_weight',
                        help='Total variation regularization weight (default %(default)s)',
                        metavar='TV_WEIGHT', default=TV_WEIGHT)
    
    parser.add_argument('--learning-rate', type=float,
                        dest='learning_rate',
                        help='Learning rate (default %(default)s)',
                        metavar='LEARNING_RATE', default=LEARNING_RATE)

    return parser


def check_opts(opts):
    """
        This function checks input params.
        Arguments:
            'opts' - ArgumentParser.parse_args() input
        Returns:
            No returned value, assert if bad parse
    """
    exists(opts.checkpoint_dir, "Checkpoint dir not found!")
    exists(opts.style, "Style path not found!")
    exists(opts.train_path, "Train path not found!")
    exists(opts.vgg_path, "VGG network data not found!")

    assert opts.epochs > 0
    assert opts.batch_size > 0
    assert opts.checkpoint_iterations > 0
    assert os.path.exists(opts.vgg_path)
    assert opts.content_weight >= 0
    assert opts.style_weight >= 0
    assert opts.tv_weight >= 0
    assert opts.learning_rate >= 0


def _get_files(dir):
    """
        Construct dir file list.
        Arguments:
            'dir' - directory for searching
        Returns:
            'files' - array of full file names
    """
    files = list_files(dir)
    return [os.path.join(dir, x) for x in files]

    
def main():
    """
        Main module function.
    """
    # Get and check input args
    parser = build_parser()
    options = parser.parse_args()
    check_opts(options)

    # Params parsing
    style_target = get_img(options.style)
    content_targets = _get_files(options.train_path)

    kwargs = {
        "epochs":options.epochs,
        "print_iterations":options.checkpoint_iterations,
        "batch_size":options.batch_size,
        "save_path":os.path.join(options.checkpoint_dir,'fns.ckpt'),
        "learning_rate":options.learning_rate
    }

    args = [
        content_targets,
        style_target,
        options.content_weight,
        options.style_weight,
        options.tv_weight,
        options.vgg_path
    ]

    # Training
    print("Starting training...")
    for preds, losses, i, epoch in optimize(*args, **kwargs):
        style_loss, content_loss, tv_loss, loss = losses
        print('Epoch %d, Iteration: %d, Loss: %s' % (epoch, i, loss))
        to_print = (style_loss, content_loss, tv_loss)
        print('style: %s, content:%s, tv: %s' % to_print)

    # Training finished
    ckpt_dir = options.checkpoint_dir
    cmd_text = 'python evaluate.py --checkpoint %s ...' % ckpt_dir
    print("Training complete. For evaluation:\n    `%s`" % cmd_text)


if __name__ == '__main__':
    main()
