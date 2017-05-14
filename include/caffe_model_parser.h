#ifndef __CAFFE_MODEL_PARSER_H__
#define __CAFFE_MODEL_PARSER_H__

#include "caffe/caffe.hpp"

using caffe::Blob;
using caffe::shared_ptr;
using caffe::vector;

namespace caffe_mp {

void get_convolution_layer_info(const caffe::ConvolutionParameter& conv_param,
                                const vector<shared_ptr<Blob<float> > >& blobs);
void get_pooling_layer_info(const caffe::PoolingParameter& pool_param);
void get_innerproduct_layer_info(const caffe::InnerProductParameter& ip_param,
                                 const vector<shared_ptr<Blob<float> > >& blobs);

}

#endif /* __CAFFE_MODEL_PARSER_H__ */
