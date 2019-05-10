# Ready modules
from argparse import ArgumentParser
import sys

# Custom modules
sys.path.insert(0, 'src')
import random, transform_img
from utils import exists, list_files


# Global consts
TMP_DIR = '.fns_frames_%s/' % random.randint(0,99999)
DEVICE = '/device:gpu:0'
BATCH_SIZE = 4


def build_parser():
    """
        Constructs input params parser.
        Returns:
            'parser' - constructed ArgumentParser
    """
    parser = ArgumentParser()
    parser.add_argument('--checkpoint', type=str,
                        dest='checkpoint', help='Checkpoint directory or .ckpt file',
                        metavar='CHECKPOINT', required=True)

    parser.add_argument('--in-path', type=str,
                        dest='in_path', help='In video path',
                        metavar='IN_PATH', required=True)
    
    parser.add_argument('--out-path', type=str,
                        dest='out', help='Path to save processed video to',
                        metavar='OUT', required=True)
    
    parser.add_argument('--tmp-dir', type=str, dest='tmp_dir',
                        help='Temporary dir for processing', metavar='TMP_DIR',
                        default=TMP_DIR)

    parser.add_argument('--device', type=str, dest='device',
                        help='Device for eval. CPU discouraged. ex: \'/device:gpu:0\'',
                        metavar='DEVICE', default=DEVICE)

    parser.add_argument('--batch-size', type=int,
                        dest='batch_size',help='Batch size for eval. default 5.',
                        metavar='BATCH_SIZE', default=BATCH_SIZE)

    parser.add_argument('--no-disk', type=bool, dest='no_disk',
                        help='Don\'t save intermediate files to disk. Default False',
                        metavar='NO_DISK', default=False)
    return parser


def check_opts(opts):
    """
        Check input params via ArgumentParser.
        Returns:
            No return value, assert if failed
    """
    exists(opts.checkpoint, "Checkpoint not defined!")
    exists(opts.in_path, "Input video not defined!")


def main():
    """
        Main module entry point.
    """
    # Parse input params
    parser = build_parser()
    opts = parser.parse_args()
    check_opts(opts)

    # Start video transformation
    transform_img.transform_video(opts.in_path, opts.out, opts.checkpoint, opts.device, opts.batch_size)

    sys.stdout.write("OUT_FILE=" + opts.out)


if __name__ == '__main__':
    main()
