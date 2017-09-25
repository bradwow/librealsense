/* License: Apache 2.0. See LICENSE file in root directory.
   Copyright(c) 2017 Intel Corporation. All Rights Reserved. */

/** \file rs2_processing.h
* \brief
* Exposes RealSense processing-block functionality for C compilers
*/


#ifndef LIBREALSENSE_RS2_PIPELINE_H
#define LIBREALSENSE_RS2_PIPELINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rs_types.h"

/**
* create pipeline
* \param[in]  ctx    context
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
*/
rs2_pipeline* rs2_create_pipeline(rs2_context* ctx, rs2_error ** error);

/**
* Retrieved the device used by the pipeline
* \param[in] ctx   context
* \param[in] pipe  pipeline
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
* \return the device used by the pipeline
*/
rs2_device* rs2_pipeline_get_device(rs2_context* ctx, rs2_pipeline* pipe, rs2_error ** error);

/**
* start streaming with default configuration or commited configuration
* \param[in] pipe  pipeline
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
*/
void rs2_start_pipeline(rs2_pipeline* pipe, rs2_error ** error);

void rs2_open_pipeline(rs2_pipeline* pipe, rs2_error ** error);

/**
* stop streaming will not change the pipeline configuration
* \param[in] pipe  pipeline
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
*/
void rs2_stop_pipeline(rs2_pipeline* pipe, rs2_error ** error);
/**
* committing a configuration to pipeline
* \param[in] stream    stream type
* \param[in] index     stream index
* \param[in] width     width
* \param[in] height    height
* \param[in] format    stream format
* \param[in] framerate    stream framerate
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
*/
void rs2_enable_pipeline_stream(rs2_pipeline* pipe, rs2_stream stream, int index, int width, int height, rs2_format format, int framerate, rs2_error ** error);

void rs2_enable_pipeline_device(rs2_pipeline* pipe, const char* serial, rs2_error ** error);

/**
*  remove all configurations from the pipeline
*/
void rs2_reset_config_streams_pipeline(rs2_pipeline* pipe, rs2_error ** error);

/**
* wait until new frame becomes available
* \param[in] pipe the pipeline
* \param[in] timeout_ms   Max time in milliseconds to wait until an exception will be thrown
* \return Set of coherent frames
*/
rs2_frame* rs2_pipeline_wait_for_frames(rs2_pipeline* pipe, unsigned int timeout_ms, rs2_error ** error);

/**
* poll if a new frame is available and dequeue if it is
* \param[in] pipe the pipeline
* \param[out] output_frame frame handle to be released using rs2_release_frame
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
* \return true if new frame was stored to output_frame
*/
int rs2_pipeline_poll_for_frames(rs2_pipeline* pipe, rs2_frame** output_frame, rs2_error ** error);

/**
* return the selected profiles of the pipeline
* \param[in] pipe the pipeline
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
* \return       list of stream profiles
*/
rs2_stream_profile_list* rs2_pipeline_get_active_streams(rs2_pipeline * pipe, rs2_error** error);

/**
* return the selected profile's count of the pipeline 
* \param[in] list the selected profiles list of the pipeline
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
* \return       list of stream profiles
*/
int rs2_pipeline_get_selection_count(const rs2_stream_profile_list* list, rs2_error** error);

/**
* return the specific profile from the selected profiles of the pipeline
* \param[in] list the selected profiles list
* \param[in] index the required stream index
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
* \return       the request stream profile
*/
const rs2_stream_profile* rs2_pipeline_get_stream_selection(const rs2_stream_profile_list* list, int index, rs2_error** error);

/**
* Return the specific profile from the selected profiles of the pipeline
* \param[in] list the selected profiles list
* \param[in] stream the required stream
* \param[in] stream the required stream index
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
* \return       the request stream profile
*/
const rs2_stream_profile* rs2_pipeline_get_stream_type_selection(const rs2_stream_profile_list* list, rs2_stream stream, int index, rs2_error** error);

/**
* delete stream profiles list
* \param[in] list        the list of supported profiles returned by rs2_get_supported_profiles
*/
void rs2_pipeline_delete_selection(rs2_stream_profile_list* list);

/**
* delete pipeline
* \param[in] pipeline to delete
*/
void rs2_delete_pipeline(rs2_pipeline* block);

/**
* Configures the pipeline to use the given playback file as the device
* The pipeline will try to create a device from the given file and match other configurations to it
* NOTE: Enabling device from file cannot be used when enabling recording, and vice versa
* \param[in] pipe    A pointer to an instance of the pipeline
* \param[in] file    Path to a recorded RealSense SDK file
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
*/
void rs2_pipeline_enable_device_from_file(rs2_pipeline* pipe, const char* file, rs2_error ** error);


/**
* Adds a request for the pipeline to record the device to file.
* This function should be called before starting the pipeline.
* After selecting the device that matches all other configuration, the pipeline will "wrap" the device
* with a recorder and use it as the device.
* Recording will begin once pipeline::Start() is called, and recording will end once pipeline::Stop() is called
* To record another session, reconfigure the pipeline.
* NOTE: Enabling device recording cannot be used when enabling device from file, and vice versa
* \param[in] pipe    A pointer to an instance of the pipeline
* \param[in] file    Path to the file to which record should be saved
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
*/
void rs2_pipeline_enable_device_from_file(rs2_pipeline* pipe, const char* file, rs2_error ** error);

#ifdef __cplusplus
}
#endif
#endif
