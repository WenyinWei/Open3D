#!/usr/bin/python
#! -*- encoding: utf-8 -*-

# This file is part of OpenMVG (Open Multiple View Geometry) C++ library.

# Python implementation of the bash script written by Romuald Perrot
# Created by @vins31
# Modified by Pierre Moulon
#
# this script is for easy use of OpenMVG
#
# usage : python openmvg.py image_dir output_dir
#
# image_dir is the input directory where images are located
# output_dir is where the project must be saved
#
# if output_dir is not present script will create it
#

# Indicate the openMVG binary directory
import sys
import subprocess
import os
OPENMVG_SFM_BIN = "C:/Users/28105/Open3D/openMVGbuild64/Windows-AMD64-Release/Release"
# Indicate the openMVG camera sensor width directory
CAMERA_SENSOR_WIDTH_DIRECTORY = "C:/Users/28105/Open3D/src/openMVG/src/software/SfM" + \
    "/../../openMVG/exif/sensor_width_database"

OPENMVS_BIN_DIR = "C:/Users/28105/Open3D/openMVSbuild64/bin/x64/Release"


# if len(sys.argv) < 3:
#     print ("Usage %s image_dir output_dir" % sys.argv[0])
#     sys.exit(1)

INPUT_IMAGE_DIR = sys.argv[1]
WORK_DIR = INPUT_IMAGE_DIR + "/.."
OUTPUT_MVG_DIR = WORK_DIR + "/MVG"
OUTPUT_MVS_DIR = WORK_DIR + "/MVS"
MVG_MATCHES_DIR = os.path.join(OUTPUT_MVG_DIR, "matches")
MVG_RECONSTRUCT_DIR = os.path.join(OUTPUT_MVG_DIR, "reconstruction_sequential")
camera_file_params = os.path.join(
    CAMERA_SENSOR_WIDTH_DIRECTORY, "sensor_width_camera_database.txt")


DO_MVG = True
if DO_MVG:
    # Create the ouput/matches folder if not present
    if not os.path.exists(OUTPUT_MVG_DIR):
        os.mkdir(OUTPUT_MVG_DIR)
    if not os.path.exists(MVG_MATCHES_DIR):
        os.mkdir(MVG_MATCHES_DIR)

    print("\n\n1. Intrinsics analysis")
    pIntrisics = subprocess.Popen([os.path.join(OPENMVG_SFM_BIN, "openMVG_main_SfMInit_ImageListing"),
                                   "-i", INPUT_IMAGE_DIR, "-o", MVG_MATCHES_DIR, "-d", camera_file_params])
    pIntrisics.wait()

    print("\n\n2. Compute features")
    pFeatures = subprocess.Popen([os.path.join(OPENMVG_SFM_BIN, "openMVG_main_ComputeFeatures"),
                                  "-i", MVG_MATCHES_DIR + "/sfm_data.json", "-o", MVG_MATCHES_DIR, "-m", "SIFT"])
    pFeatures.wait()

    print("\n\n3. Compute matches")
    pMatches = subprocess.Popen([os.path.join(OPENMVG_SFM_BIN, "openMVG_main_ComputeMatches"),
                                 "-i", MVG_MATCHES_DIR + "/sfm_data.json", "-o", MVG_MATCHES_DIR])
    pMatches.wait()

    # Create the reconstruction if not present
    if not os.path.exists(MVG_RECONSTRUCT_DIR):
        os.mkdir(MVG_RECONSTRUCT_DIR)

    # print("\n\n4. Do Sequential/Incremental reconstruction")
    # pRecons = subprocess.Popen([os.path.join(OPENMVG_SFM_BIN, "openMVG_main_IncrementalSfM"),
    #                             "-i", MVG_MATCHES_DIR + "/sfm_data.json", "-m", MVG_MATCHES_DIR, "-o",
    #                             MVG_RECONSTRUCT_DIR])
    # pRecons.wait()

    # print("\n\n5. Colorize Structure")
    # pRecons = subprocess.Popen([os.path.join(OPENMVG_SFM_BIN, "openMVG_main_ComputeSfM_DataColor"), "-i",
    #                             MVG_RECONSTRUCT_DIR + "/sfm_data.bin", "-o",
    #                             os.path.join(MVG_RECONSTRUCT_DIR, "colorized.ply")])
    # pRecons.wait()

    # print("\n\n6. Transfrom OpenMVG2OpenMVS")
    # pRecons = subprocess.Popen(
    #     [os.path.join(OPENMVG_SFM_BIN, "openMVG_main_openMVG2openMVS"), "-i", MVG_RECONSTRUCT_DIR +
    #      "/sfm_data.bin", "-d", OUTPUT_MVS_DIR, "-o",
    #      os.path.join(OUTPUT_MVS_DIR, "scene.mvs")])
    # pRecons.wait()

    # # optional, compute final valid structure from the known camera poses
    print("5'. Structure from Known Poses (robust triangulation)")
    pRecons = subprocess.Popen([os.path.join(OPENMVG_SFM_BIN, "openMVG_main_ComputeStructureFromKnownPoses"),
                                "-i", OUTPUT_MVG_DIR +
                                "/sfm_data.bin", "-m", MVG_MATCHES_DIR, "-f", os.path.join(
                                    MVG_MATCHES_DIR, "matches.f.bin"),
                                "-o", os.path.join(OUTPUT_MVG_DIR, "robust.bin")])
    pRecons.wait()

    pRecons = subprocess.Popen([os.path.join(OPENMVG_SFM_BIN, "openMVG_main_ComputeSfM_DataColor"),  "-i",
                                OUTPUT_MVG_DIR+"/robust.bin", "-o", os.path.join(OUTPUT_MVG_DIR, "robust_colorized.ply")])
    pRecons.wait()

    print("\n\n6. Transfrom OpenMVG2OpenMVS")
    pRecons = subprocess.Popen(
        [os.path.join(OPENMVG_SFM_BIN, "openMVG_main_openMVG2openMVS"), "-i", MVG_RECONSTRUCT_DIR +
         "/robust.bin", "-d", OUTPUT_MVS_DIR, "-o",
         os.path.join(OUTPUT_MVS_DIR, "scene.mvs")])
    pRecons.wait()

DO_MVS = False
if DO_MVS:
    if not os.path.exists(OUTPUT_MVS_DIR):
        os.mkdir(OUTPUT_MVS_DIR)

    DenseVersion = False
    # DenseVersion = False
    if DenseVersion:
        print("\n\n6. Densify PointCloud by MVS")
        pRecons = subprocess.Popen([os.path.join(
            OPENMVS_BIN_DIR, "DensifyPointCloud"), os.path.join(OUTPUT_MVS_DIR, "scene.mvs")])
        pRecons.wait()

        print("\n\n7. Reconstruct Mesh")
        pRecons = subprocess.Popen([os.path.join(
            OPENMVS_BIN_DIR, "ReconstructMesh"), os.path.join(OUTPUT_MVS_DIR, "scene_dense.mvs")])
        pRecons.wait()

        print("\n\n8. Texture Mesh")
        pRecons = subprocess.Popen([os.path.join(OPENMVS_BIN_DIR, "TextureMesh"), os.path.join(
            OUTPUT_MVS_DIR, "scene_dense_mesh.mvs")])
        pRecons.wait()
    else:
        print("\n\n7. Reconstruct Mesh")
        pRecons = subprocess.Popen([os.path.join(
            OPENMVS_BIN_DIR, "ReconstructMesh"), os.path.join(OUTPUT_MVS_DIR, "scene.mvs")])
        pRecons.wait()

        print("\n\n8. Texture Mesh")
        pRecons = subprocess.Popen([os.path.join(OPENMVS_BIN_DIR, "TextureMesh"), os.path.join(
            OUTPUT_MVS_DIR, "scene_mesh.mvs")])
        pRecons.wait()
