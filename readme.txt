ml_core:
	1. transform_img.py - transform style for single image
		Arguments:
			--checkpoint - pre-trained CNN full name. Required
			--in-path - full path to imput image or folder with input images. Required
			--out-path - full path to output image or folder woth output images. Required
			--device - processing device type. Default: '/cpu:0'
			--batch-size - processing data batch size. Default: 4
			--allow-different-dimensions - use only for multiple input with different dimensions

	2. transform_video.py - transform style for video
		Arguments:
			--checkpoint - pre-trained CNN full name. Required.
			--in-path - full path to input video file. Required.
			--out-path - full path to output video file. Required.
			--tmp-dir - directory for saving temporary transformed files. Default: '.fns_frames_%s/' % random.randint(0,99999).
			--device - processing device type. Default: '/device:gpu:0'.
			--batch-size - processing data batch size. Default: 8.
			--no-disk - Don't use disk for tmp frames saving, uses RAM. Default: False.

	3. train.py - train new style checkpoint
		Arguments:
			--checkpoint-dir - Directory to save checkpoint in. Required.
			--style - Path to style image. Required.
			--train-path: Path to training images folder. Required.
			--epochs - Epochs to train for. Default: 2.
			--batch_size - Batch size for training. Default: 4.
			--checkpoint-iterations - Number of iterations to go for between checkpoints. Default: 2000.
			--vgg-path - Path to VGG19 network (default). Can pass VGG16 if you want to try out other loss functions. Required.
			--content-weight - Weight of content in loss function. Default: 7.5e0.
			--style-weight - Weight of style in loss function. Default: 1e2.
			--tv-weight - Weight of total variation term in loss function. Default: 2e2.
			--learning-rate - Learning rate for optimizer. Default: 1e-3.
			

Depends:
	1. Python (v3.6.8):
		- tensorflow-gpu (v.1.13.0)
		- Pillow (v6.0.0)
		- scipy (v1.2.1)
		- numpy (v1.16.2)

	2. NVIDIA CUDA:
		- cuda_10.0.13
		- cudnn_10.0
		- latest NVIDIA GPU drivers

	3. Qt/C++:
		- C++14
		- QtFramework (v5.9.6) with multimedia module
		- K-Lite base codecs pack
		- LAV filters pack
		- Qt5Core.dll
		- Qt5Gui.dll
		- Qt5Multimedia.dll
		- Qt5MultimediaWidgets.dll
		- Qt5Network.dll
		- Qt5OpenGL.dll
		- Qt5Widgets.dll
		- Qt5Xml.dll
