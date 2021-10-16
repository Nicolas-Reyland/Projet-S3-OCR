// model.c
#include "model.h"

void _nn_Model_saveArchitectureFn(nn_Model* model, char* path)
{
  //
}

void _nn_Model_saveWeightsAndBias(nn_Model* model, char* path)
{
  //
}

void _nn_Model_saveModel(nn_Model* model, char* dirpath)
{
  //
}

nn_Model* createModel(size_t num_layers, nn_ShapeDescription model_architecture[], activation activations[], losses loss, optimizer optimizer)
{
  nn_ModelLayers* layers = _nn_createModelLayers(num_layers - 2, model_architecture, activations);
  // malloc struct
  nn_Model* model = mem_malloc(sizeof(nn_Model));
  model->layers = layers;
  model->loss = loss;
  model->optimizer = optimizer;
  // add functions to struct
  model->saveArchitecture = &_nn_Model_saveArchitectureFn;
  model->saveWeightsAndBias = &_nn_Model_saveWeightsAndBias;
  model->saveModel = &_nn_Model_saveModel;
  return model;
}

void freeModel(nn_Model* model)
{
  _nn_freeModelLayers(model->layers);
  verbose("freed model layers");
  mem_free(model);
}

// nn_Model* loadModel(char* path);
