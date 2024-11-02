#!/bin/bash

# Usage: compile_proto.sh <proto_file> <output_dir>
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <proto_file> <output_dir>"
    exit 1
fi

PROTO_FILE=$1
OUTPUT_DIR=$2
PROTO_NAME=$(basename "$PROTO_FILE" .proto)

# Create output directories
mkdir -p "$OUTPUT_DIR/python"
mkdir -p "$OUTPUT_DIR/cpp"
mkdir -p "$OUTPUT_DIR/js"

# Generate Python code
protoc --proto_path=$(dirname "$PROTO_FILE") \
       --python_out="$OUTPUT_DIR/python" \
       --pyi_out="$OUTPUT_DIR/python" \
       "$PROTO_FILE"

# Generate C++ code
protoc --proto_path=$(dirname "$PROTO_FILE") \
       --cpp_out="$OUTPUT_DIR/cpp" \
       "$PROTO_FILE"

# Generate JavaScript code
protoc --proto_path=$(dirname "$PROTO_FILE") \
       --js_out=import_style=commonjs,binary:"$OUTPUT_DIR/js" \
       --grpc-web_out=import_style=typescript,mode=grpcwebtext:"$OUTPUT_DIR/js" \
       "$PROTO_FILE"

echo "Generated files:"
echo "Python: $OUTPUT_DIR/python/${PROTO_NAME}_pb2.py"
echo "Python types: $OUTPUT_DIR/python/${PROTO_NAME}_pb2.pyi"
echo "C++: $OUTPUT_DIR/cpp/${PROTO_NAME}.pb.h and ${PROTO_NAME}.pb.cc"
echo "JavaScript: Check $OUTPUT_DIR/js/ directory" 