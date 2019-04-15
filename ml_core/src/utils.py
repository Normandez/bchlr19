import scipy.misc, os
import numpy as np


def save_img(out_path, img):
  """
    Save image to file.
    Arguments:
      'out_path' - path to save
      'img' - input image represented as array
  """
  img = np.clip(img, 0, 255).astype(np.uint8)
  scipy.misc.imsave(out_path, img)


def scale_img(img_path, img_scale):
  """
    Scale input image.
    Arguments:
      'img_path' - imput image path
      'img_scale' - scailng x-rate (float)

    Return:
      'img_target' - scaled image

  """
  scale = float(img_scale)
  o0, o1, o2 = scipy.misc.imread(img_path, mode='RGB').shape

  new_shape = (int(o0 * scale), int(o1 * scale), o2)
  img_target = get_img(img_path, img_size=new_shape)

  return img_target


def get_img(img_path, img_size=False):
  """
    This function read image from disk.
    Arguments:
      'src' - drive source path
      'img_size' - image rate (False by default, when scailing not needed)
    Return:
      'img' - loaded/scaled image
  """
  img = scipy.misc.imread(img_path, mode='RGB')

  if not (len(img.shape) == 3 and img.shape[2] == 3):
    img = np.dstack((img,img,img))

  if img_size != False:
    img = scipy.misc.imresize(img, img_size)

  return img


def exists(p, msg):
  """
    Path existing checker.
  """
  assert os.path.exists(p), msg


def list_files(in_path):
  """
    Construct file list of path.
    Arguments:
      'in_path' - files contains path(dir)
    Returns:
      'files' - array of files
  """
  files = []
  for (dirpath, dirnames, filenames) in os.walk(in_path):
    files.extend(filenames)
    break

  return files
