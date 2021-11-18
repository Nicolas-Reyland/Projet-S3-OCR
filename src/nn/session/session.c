// session.c

#include "session.h"

void _nn_train(struct nn_Session* session, nn_Model* model)
{
	// TODO: make this an argument, in session or directly here
	size_t nb_verb_step = 100;

	nn_InOutTuple** tuple_array = iot_linked_list_to_array(
		session->dataset->train->data_collection->data);
	size_t sample_size =session->dataset->train->data_collection->data->length;

	bool loss_threshold_condition = true;

	size_t epoch = 0;
	while (epoch < session->nb_epochs && loss_threshold_condition)
	{
		/*if(session->verb_mode)
		{*/
			verbose("Epoch number: %ld",epoch);
		/*}*/
		shuffleArray(tuple_array,sample_size);
		size_t i = 0;
		double loss_buffer = 0;
		while(i < sample_size)
		{
			/*if(session->verb_mode)
			{
				verbose("Training Tuple:");
				tuple_array[i]->printTuple(tuple_array[i]);
			}*/
			_nn_feedForward(model,tuple_array[i]->input->values);

			//we calculate the loss function
			double error = applyLosses(
				model->layers[model->num_layers - 1],
				tuple_array[i]->output->values,
				model->loss);
			/*if(session->verb_mode)
				verbose("Losses error = %f",error);*/
			loss_buffer += error;
			/*if(session->verb_mode)
			{
				model->printModelLayers(model);
				model->printModelLayersValues(model);
			}*/

			_nn_backPropagation(model, tuple_array[i]->output->values);
			_nn_updateWeights(model, session->learning_rate);
			i++;

			if (session->verb_mode && i % nb_verb_step == 0) {
				verbose("Losses error = %lf", error);
			}
		}

		loss_buffer /= sample_size;
		// we continue as long as we do not reached loss threshold
		// or we continue as long as we have epochs to do
		loss_threshold_condition =
			!session->stop_on_loss_threshold_reached ||
			loss_buffer > session->loss_threshold;
		epoch++;
	}
	return;
}

void _nn_test(struct nn_Session* session, nn_Model* model)
{
	nn_InOutTuple** tuple_array = iot_linked_list_to_array(
		session->dataset->test->data_collection->data);
	size_t sample_size =session->dataset->test->data_collection->data->length;

	shuffleArray(tuple_array,sample_size);
	for(size_t i = 0; i < sample_size; i++)
	{
		verbose("Testing Tuple:");
		tuple_array[i]->printTuple(tuple_array[i]);
		_nn_feedForward(model, tuple_array[i]->input->values);

		verbose("Result:");
		for(size_t j = 0; j < model->layers[model->num_layers - 1]->num_nodes; j++)
			verbose_no_endline("%lf ",
			model->layers[model->num_layers - 1]->nodes[j]->value);
		verbose("");
		//we calculate the loss function
		double error = applyLosses(
		model->layers[model->num_layers - 1],
		tuple_array[i]->output->values,
		model->loss);
		verbose("Losses error = %f",error);
	}
}

nn_Session* createSession(nn_DataSet* dataset, unsigned int nb_epochs,
double loss_threshold, bool stop_on_loss_threshold_reached, bool verbose,
double learning_rate)
{
	nn_Session* session = mem_malloc(sizeof(nn_Session));

	session->dataset 			= dataset;
	session->nb_epochs 			= nb_epochs;
	session->loss_threshold 	= loss_threshold;
	session->verb_mode			= verbose;
	session->learning_rate		= learning_rate;

	session->stop_on_loss_threshold_reached = stop_on_loss_threshold_reached;

	session->train 	= &_nn_train;
	session->test	= &_nn_test;

	return session;
}

void freeSession(nn_Session* session)
{
	_nn_freeDataSet(session->dataset);
	mem_free(session);
}
