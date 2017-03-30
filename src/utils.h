/*
 Copyright (c) 2016 Fabio Nicotra.
 All rights reserved.
 
 Redistribution and use in source and binary forms are permitted
 provided that the above copyright notice and this paragraph are
 duplicated in all such forms and that any documentation,
 advertising materials, and other materials related to such
 distribution and use acknowledge that the software was developed
 by the copyright holder. The name of the
 copyright holder may not be used to endorse or promote products derived
 from this software without specific prior written permission.
 THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef __PS_UTILS_H
#define __PS_UTILS_H

#include <math.h>

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

#define getNeuronLayer(neuron) ((PSLayer*) neuron->layer)
#define getLayerNetwork(layer) ((PSNeuralNetwork*) layer->network)
#define shouldApplyDerivative(network) (network->loss != crossEntropyLoss)

#ifdef USE_AVX

#define AVXDotProduct(size, x, y, res, i, is_recurrent, t) do { \
    int avx_step_len = AVXGetDotStepLen(size); \
    avx_dot_product dot_product = AVXGetDotProductFunc(size); \
    int avx_steps = size / avx_step_len, avx_step; \
    for (avx_step = 0; avx_step < avx_steps; avx_step++) { \
        double * x_vector = x + i; \
        if (is_recurrent) x_vector += (t * size); \
        double * y_vector = y + i; \
        res += dot_product(x_vector, y_vector); \
        i += avx_step_len; \
    } \
} while (0)

#define AVXMultiplyValue(size, x, y, val, i, is_recurrent, t, mode) do { \
    int avx_step_len = AVXGetStepLen(size); \
    int avx_steps = size / avx_step_len, avx_step; \
    avx_multiply_value multiply_val = AVXGetMultiplyValFunc(size); \
    for (avx_step = 0; avx_step < avx_steps; avx_step++) { \
        double * x_vector = x + i; \
        if (is_recurrent) x_vector += (t * size); \
        multiply_val(x_vector, val, y + i, mode); \
        i += avx_step_len; \
    } \
} while (0)

#endif

#define printMemoryErrorMsg() PSErr(NULL, "Could not allocate memory!")

void PSErr(const char* tag, char* fmt, ...);

/* Activation Functions */

double sigmoid(double val);

double sigmoid_derivative(double val);

double relu(double val);

double relu_derivative(double val);

double tanh_derivative(double val);

/* Network Functions */

void PSAbortLayer(PSNeuralNetwork * network, PSLayer * layer);

/* Misc */


double normalized_random();

double gaussian_random(double mean, double stddev);

#endif //__PS_UTILS_H