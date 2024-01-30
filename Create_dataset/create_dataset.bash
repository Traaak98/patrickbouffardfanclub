#! /bin/bash

echo "Path to dataset: $1"
echo "Path to output: $2"

for genre_dir in `ls $1`
do
  for audio_file in `ls $1/$genre_dir/*.au`
  do
    echo "Processing $audio_file"
    ./load_and_extract $audio_file $2
  done
done

