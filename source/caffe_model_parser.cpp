#include "caffe_model_parser.h"

#include <iostream>

namespace caffe_mp {

void get_convolution_layer_info(const caffe::ConvolutionParameter& conv_param,
                                const vector<shared_ptr<Blob<float> > >& blobs) {
  std::cout << "Num outputs: " << conv_param.num_output() << std::endl;
  return;
}

void get_pooling_layer_info(const caffe::PoolingParameter& pool_param) {
  std::cout << "kernel size: " << pool_param.kernel_size() << std::endl;
  return;
}

void get_innerproduct_layer_info(const caffe::InnerProductParameter& ip_param,
                                 const vector<shared_ptr<Blob<float> > >& blobs) {
  // get layer parameters
  std::cout << "Num outputs: " << ip_param.num_output() << std::endl;

  // get layer weights
  for (const auto& blob : blobs) {
    std::cout << blob->num_axes() << std::endl;
    if (blob->num_axes() == 2) continue; // skip biases
    const vector<int>& blob_shape = blob->shape();
    int num = blob_shape[0];
    int chanels = blob_shape[1];
    std::cout << "number: " << num << " channels: " << chanels << std::endl;
    std::cout << "shape string: " << blob->shape_string() << "\n";
    std::cout << "count: " << blob->count() << "\n";
    // get weights
    // const float *weight = blob->cpu_data();
  }
}

} // namespace caffe_mp
