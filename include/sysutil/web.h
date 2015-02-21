#pragma once

#include <psl1ght/types.h>

typedef struct {
  uint32_t version;
  uint32_t heap_size;
  uint32_t functions;
  uint32_t tab_count;
  uint32_t size_mode;
  uint32_t view_restriction;

  uint32_t unknown_mimetype_cb;
  uint32_t error_cb;
  uint32_t status_error_cb;
  uint32_t notify_cb;
  uint32_t request_cb;

  uint32_t x, y;
  uint32_t width, height;

  float resolution_factor;

  uint32_t magic_number;
} web_browser_config;


#define WEBBROWSER_INITIALIZING_FINISHED  1
#define WEBBROWSER_SHUTDOWN_FINISHED      4
#define WEBBROWSER_LOADING_FINISHED       5
#define WEBBROWSER_UNLOADING_FINISHED     7
#define WEBBROWSER_RELEASED               9
#define WEBBROWSER_GRABBED               11

int webBrowserConfig(web_browser_config *cfg, unsigned int version);

int webBrowserConfigSetFunction(web_browser_config *cfg, unsigned int flags);

int webBrowserConfigSetTabCount(web_browser_config *cfg, unsigned int tabs);

int webBrowserConfigSetHeapSize(web_browser_config *cfg, unsigned int size);

int webBrowserConfigSetUnknownMIMETypeHook(web_browser_config *cfg,
                                           void *cb, void *args);

int webBrowserEstimate(web_browser_config *cfg, int *size);

int webBrowserInitialize(void *cb, uint64_t container);

int webBrowserCreate(web_browser_config *cfg, const char *url);

int webBrowserDestroy(void);

void webBrowserShutdown(void);

void webBrowserSetRequestHook(web_browser_config *cfg, void *cb, void *aux);
