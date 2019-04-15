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
			
