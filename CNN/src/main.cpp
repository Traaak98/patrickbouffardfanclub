//
// Created by apolline on 16/01/24.
//

// tensorflow lite
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/interpreter.h"


int main(int argc, char** argv) {
    // Load the model
    std::unique_ptr<tflite::FlatBufferModel> model =
            tflite::FlatBufferModel::BuildFromFile(filename);

// Build the interpreter
    tflite::ops::builtin::BuiltinOpResolver resolver;
    std::unique_ptr<tflite::Interpreter> interpreter;
    tflite::InterpreterBuilder(*model, resolver)(&interpreter);

// Resize input tensors, if desired.
    interpreter->AllocateTensors();

    float* input = interpreter->typed_input_tensor<float>(0);
// Fill `input`.

    interpreter->Invoke();

    float* output = interpreter->typed_output_tensor<float>(0);


    return 0;
}