#include <iostream>
#include <string>
#include <vector>

#include "caffe/caffe.hpp"
#include "caffe_model_parser.h"

using caffe::Caffe;
using caffe::Net;
using caffe::Layer;
using caffe::Blob;
using caffe::shared_ptr;
using caffe::vector;
using caffe::string;
using namespace caffe_mp;

static std::string modelParamFile = "/home/sourabh/Work/caffe/models/bvlc_alexnet/deploy.prototxt";
static std::string modelWeightsFile = "/home/sourabh/Work/caffe/models/bvlc_alexnet/bvlc_alexnet.caffemodel";


int main(int argc, char **argv) {
  Caffe::set_mode(Caffe::CPU);

  // Instantiate the caffe net.
  Net<float> caffe_net(modelParamFile, caffe::TEST);
  caffe_net.CopyTrainedLayersFrom(modelWeightsFile);

  const vector<shared_ptr<Layer<float> > >& layers = caffe_net.layers();
  for (const auto& layer : layers) {
    const caffe::LayerParameter& param = layer->layer_param();
    string layer_type = layer->type();

    if (layer_type == "Convolution") {
      const vector<shared_ptr<Blob<float> > >& blobs = layer->blobs();
      get_convolution_layer_info(param.convolution_param(), blobs);
    } else if (layer_type == "Pooling") {
      get_pooling_layer_info(param.pooling_param());
    } else if (layer_type == "InnerProduct") {
      const vector<shared_ptr<Blob<float> > >& blobs = layer->blobs();
      get_innerproduct_layer_info(param.inner_product_param(), blobs);
    } else {
      std::cerr << "Unsupported Layer: " << layer_type << std::endl;
    }
  }

  return 0;
}
