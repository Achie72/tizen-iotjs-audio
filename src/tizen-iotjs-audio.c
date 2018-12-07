#include <tizen.h>
#include <service_app.h>
#include <iotjs_tizen_service_app.h>
#include "tizen-iotjs-audio.h"
#include <sound_manager.h>
#include <media/recorder.h>
#include <stdio.h>
#include <streamrecorder.h>
#include <time.h>

#define LOG_TAG "IOTJS"
#define FILENAME_PREFIX "AUDIO"

static recorder_h g_recorder;
int error_code = 0;
char filename[256] = {'\0'};
size_t size;

bool service_app_create(void *data)
{
	// Todo: add your code here.
	return true;
}

void service_app_terminate(void *data)
{
	// Todo: add your code here.
	return;
}

void service_app_control(app_control_h app_control, void *data)
{
	// Todo: add your code here.

	// Emit 'appControl' event to the JavaScript side.
	iotjs_tizen_app_control_cb(app_control, data);
	return;
}

static void
service_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	return;
}

static void
service_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
service_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
service_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

// static bool
// _recorder_expect_state(recorder_h recorder, recorder_state_e expected_state)
// {
//     recorder_state_e state;
//     int error_code = recorder_get_state(recorder, &state);
//
//     dlog_print(DLOG_INFO, LOG_TAG, "recorder state = %d, expected recorder state = %d", state, expected_state);
//     if (state == expected_state)
//         return true;
//
//     return false;
// }
//
// static void
// _state_changed_cb(recorder_state_e previous, recorder_state_e current, bool by_policy, void *user_data)
// {
//     dlog_print(DLOG_INFO, LOG_TAG, "_recorder_state_changed_cb (prev: %d, curr: %d)\n", previous, current);
// }
//
// void input_init () {
//   /* Create the audio recorder handle */
//   int error_code = recorder_create_audiorecorder(&g_recorder);
//   if (error_code != RECORDER_ERROR_NONE)
//       dlog_print(DLOG_ERROR, LOG_TAG, "fail to create an Audio Recorder: error code = %d", error_code);
//
//   error_code = recorder_set_state_changed_cb(g_recorder, _state_changed_cb, NULL);
//   if( error_code != RECORDER_ERROR_NONE ) {
//     dlog_print(DLOG_INFO, LOG_TAG, "Mic ready");
//   } else {
//     dlog_print(DLOG_ERROR, LOG_TAG, "Failed to ready mic");
//   }
//
//
//   /* Set the audio encoder */
//   /* PCM for .wav format */
//   error_code = recorder_set_audio_encoder(g_recorder, RECORDER_AUDIO_CODEC_PCM 	);
//   if( error_code != RECORDER_ERROR_NONE ) {
//     dlog_print(DLOG_INFO, LOG_TAG, " Encoder set");
//   } else {
//     dlog_print(DLOG_ERROR, LOG_TAG, "Encoder set error");
//   }
//
//   /* Set the file format according to the audio encoder */
//   /* wav format corresponds the PCM codec */
//   error_code = recorder_set_file_format(g_recorder, RECORDER_FILE_FORMAT_WAV);
//   if( error_code != RECORDER_ERROR_NONE ) {
//     dlog_print(DLOG_INFO, LOG_TAG, " Fileformat set");
//   } else {
//     dlog_print(DLOG_ERROR, LOG_TAG, "Encoder seting file format");
//   }
//
//   /* Initialize the file to be saved */
//   size = snprintf(filename, sizeof(filename), "%s/%srecording.wav",
//                       app_get_data_path(), FILENAME_PREFIX);
//
//
//   /* Set the full path and file name */
//   /* Set the file name according to the file format */
//   error_code = recorder_set_filename(g_recorder, filename);
//   if( error_code != RECORDER_ERROR_NONE ) {
//     dlog_print(DLOG_INFO, LOG_TAG, "Full path");
//   } else {
//     dlog_print(DLOG_ERROR, LOG_TAG, "Full path");
//   }
//
//   /* SET FILE DATA */
//   /* Set the maximum file size to 1024 (kB) */
//   error_code = recorder_attr_set_size_limit(g_recorder, 1024);
//   if( error_code != RECORDER_ERROR_NONE ) {
//     dlog_print(DLOG_INFO, LOG_TAG, " Size Limit");
//   } else {
//     dlog_print(DLOG_ERROR, LOG_TAG, "ERROR size limit");
//   }
//   /* Set the audio encoder bitrate */
//   error_code = recorder_attr_set_audio_encoder_bitrate(g_recorder, 28800);
//   if( error_code != RECORDER_ERROR_NONE ) {
//     dlog_print(DLOG_INFO, LOG_TAG, " Bitrate set");
//   } else {
//     dlog_print(DLOG_ERROR, LOG_TAG, "ERROR Bitrate");
//   }
//   /* Set the audio device to microphone */
//   error_code = recorder_attr_set_audio_device(g_recorder, RECORDER_AUDIO_DEVICE_MIC);
//   if( error_code != RECORDER_ERROR_NONE ) {
//     dlog_print(DLOG_INFO, LOG_TAG, " Set audio Input to mic");
//   } else {
//     dlog_print(DLOG_ERROR, LOG_TAG, "ERROR Set audio Input to mic");
//   }
//   /* Set the audio sample rate */
//   error_code = recorder_attr_set_audio_samplerate(g_recorder, 44100);
//   if( error_code != RECORDER_ERROR_NONE ) {
//     dlog_print(DLOG_INFO, LOG_TAG, " Samplerate set");
//   } else {
//     dlog_print(DLOG_ERROR, LOG_TAG, "ERROR  Samplerate set");
//   }
//
//     dlog_print(DLOG_INFO, "IOTJS", "ALMAFA");
//
// }
//
int main(int argc, char* argv[])
{
	char ad[50] = {0,};
	service_app_lifecycle_callback_s event_callback;
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = service_app_create;
	event_callback.terminate = service_app_terminate;
	event_callback.app_control = service_app_control;

	service_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, service_app_low_battery, &ad);
	service_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, service_app_low_memory, &ad);
	service_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, service_app_lang_changed, &ad);
	service_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, service_app_region_changed, &ad);



  int error_code = recorder_create_audiorecorder(&g_recorder);
  // dlog_print(DLOG_INFO, "IOTJS", "fail to create an Audio Recorder: error code = %d", error_code);


  //input_init();

  /* audio recorder must be in the RECORDER_STATE_READY */
  // error_code = recorder_prepare(g_recorder);
  //
  //
  // error_code = recorder_start(g_recorder);
  //
  //
  // /* ide */
  // /* Stop the recorder and save the recorded data to a file */
  // if (_recorder_expect_state(g_recorder, RECORDER_STATE_RECORDING) || _recorder_expect_state(g_recorder, RECORDER_STATE_PAUSED)) {
  //     error_code = recorder_commit(g_recorder);
  //     if (error_code != RECORDER_ERROR_NONE) {
  //         dlog_print(DLOG_ERROR, LOG_TAG, "error code = %d", error_code);
  //
  //         return true;
  //     }
  // }
  //
  // error_code = recorder_unprepare(g_recorder);
  // error_code = recorder_destroy(g_recorder);
  //
  // if (error_code != RECORDER_ERROR_NONE)
  //     dlog_print(DLOG_ERROR, LOG_TAG, "fail to destroy recorder: error code = %d", error_code);

	return iotjs_service_app_start(argc, argv, "index.js", &event_callback, ad);
}
