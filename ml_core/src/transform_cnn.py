import tensorflow as tf


# Default weights STD-dev
WEIGHTS_INIT_STDDEV = .1


def net(image):
    """
        Construct CNN.
        Params:
            'image' - TF placeholder
        Returns:
            'net' - constructed CNN
    """
    conv1 = _conv_layer(image, 32, 9, 1)
    conv2 = _conv_layer(conv1, 64, 3, 2)
    conv3 = _conv_layer(conv2, 128, 3, 2)
    resid1 = _residual_block(conv3, 3)
    resid2 = _residual_block(resid1, 3)
    resid3 = _residual_block(resid2, 3)
    resid4 = _residual_block(resid3, 3)
    resid5 = _residual_block(resid4, 3)
    conv_t1 = _conv_transpose_layer(resid5, 64, 3, 2)
    conv_t2 = _conv_transpose_layer(conv_t1, 32, 3, 2)
    conv_t3 = _conv_layer(conv_t2, 3, 9, 1, relu=False)
    net = tf.nn.tanh(conv_t3) * 150 + 255./2
    return net


def _conv_layer(net, num_filters, filter_size, strides, relu=True):
    """
        Construct convolution NN layer for input 'net' with setted params.
    """
    weights_init = _conv_init_vars(net, num_filters, filter_size)
    strides_shape = [1, strides, strides, 1]
    net = tf.nn.conv2d(net, weights_init, strides_shape, padding='SAME')
    net = _instance_norm(net)
    if relu:
        net = tf.nn.relu(net)

    return net


def _conv_transpose_layer(net, num_filters, filter_size, strides):
    """
        Constuct Convolution transposed NN layer for input 'net' with setted params.
    """

    weights_init = _conv_init_vars(net, num_filters, filter_size, transpose=True)

    batch_size, rows, cols, in_channels = [i.value for i in net.get_shape()]
    new_rows, new_cols = int(rows * strides), int(cols * strides)

    new_shape = [batch_size, new_rows, new_cols, num_filters]
    tf_shape = tf.stack(new_shape)
    strides_shape = [1,strides,strides,1]

    net = tf.nn.conv2d_transpose(net, weights_init, tf_shape, strides_shape, padding='SAME')
    net = _instance_norm(net)
    return tf.nn.relu(net)


def _residual_block(net, filter_size=3):
    """
        Construct residual NN layer.
    """
    tmp = _conv_layer(net, 128, filter_size, 1)
    return net + _conv_layer(tmp, 128, filter_size, 1, relu=False)


def _instance_norm(net, train=True):
    """
        Layer normalization function.
    """
    batch, rows, cols, channels = [i.value for i in net.get_shape()]
    var_shape = [channels]
    mu, sigma_sq = tf.nn.moments(net, [1,2], keep_dims=True)
    shift = tf.Variable(tf.zeros(var_shape))
    scale = tf.Variable(tf.ones(var_shape))
    epsilon = 1e-3
    normalized = (net-mu)/(sigma_sq + epsilon)**(.5)
    return scale * normalized + shift


def _conv_init_vars(net, out_channels, filter_size, transpose=False):
    """
        Construct weights and bias for current 'net' CNN layer.
    """
    _, rows, cols, in_channels = [i.value for i in net.get_shape()]
    if not transpose:
        weights_shape = [filter_size, filter_size, in_channels, out_channels]
    else:
        weights_shape = [filter_size, filter_size, out_channels, in_channels]

    weights_init = tf.Variable(tf.truncated_normal(weights_shape, stddev=WEIGHTS_INIT_STDDEV, seed=1), dtype=tf.float32)
    return weights_init
