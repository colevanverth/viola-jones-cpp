#!/bin/bash

make
./image_setup.out ../dataset/non_face_raw ../dataset/non_face_edited
make clean
