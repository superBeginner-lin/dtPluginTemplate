// Copyright (c) 2023 Marshall A. Greenblatt. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//
// $hash=ad6d3845b150f22b88a71dafa601ef01c9579824$
//

#ifndef CEF_INCLUDE_CAPI_CEF_EXTENSION_HANDLER_CAPI_H_
#define CEF_INCLUDE_CAPI_CEF_EXTENSION_HANDLER_CAPI_H_
#pragma once

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_browser_capi.h"
#include "include/capi/cef_extension_capi.h"
#include "include/capi/cef_stream_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _cef_client_t;

///
/// Callback structure used for asynchronous continuation of
/// cef_extension_handler_t::GetExtensionResource.
///
typedef struct _cef_get_extension_resource_callback_t {
  ///
  /// Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  /// Continue the request. Read the resource contents from |stream|.
  ///
  void(CEF_CALLBACK* cont)(struct _cef_get_extension_resource_callback_t* self,
                           struct _cef_stream_reader_t* stream);

  ///
  /// Cancel the request.
  ///
  void(CEF_CALLBACK* cancel)(
      struct _cef_get_extension_resource_callback_t* self);
} cef_get_extension_resource_callback_t;

///
/// Implement this structure to handle events related to browser extensions. The
/// functions of this structure will be called on the UI thread. See
/// cef_request_context_t::LoadExtension for information about extension
/// loading.
///
typedef struct _cef_extension_handler_t {
  ///
  /// Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  /// Called if the cef_request_context_t::LoadExtension request fails. |result|
  /// will be the error code.
  ///
  void(CEF_CALLBACK* on_extension_load_failed)(
      struct _cef_extension_handler_t* self,
      cef_errorcode_t result);

  ///
  /// Called if the cef_request_context_t::LoadExtension request succeeds.
  /// |extension| is the loaded extension.
  ///
  void(CEF_CALLBACK* on_extension_loaded)(struct _cef_extension_handler_t* self,
                                          struct _cef_extension_t* extension);

  ///
  /// Called after the cef_extension_t::Unload request has completed.
  ///
  void(CEF_CALLBACK* on_extension_unloaded)(
      struct _cef_extension_handler_t* self,
      struct _cef_extension_t* extension);

  ///
  /// Called when an extension needs a browser to host a background script
  /// specified via the "background" manifest key. The browser will have no
  /// visible window and cannot be displayed. |extension| is the extension that
  /// is loading the background script. |url| is an internally generated
  /// reference to an HTML page that will be used to load the background script
  /// via a "<script>" src attribute. To allow creation of the browser
  /// optionally modify |client| and |settings| and return false (0). To cancel
  /// creation of the browser (and consequently cancel load of the background
  /// script) return true (1). Successful creation will be indicated by a call
  /// to cef_life_span_handler_t::OnAfterCreated, and
  /// cef_browser_host_t::IsBackgroundHost will return true (1) for the
  /// resulting browser. See https://developer.chrome.com/extensions/event_pages
  /// for more information about extension background script usage.
  ///
  int(CEF_CALLBACK* on_before_background_browser)(
      struct _cef_extension_handler_t* self,
      struct _cef_extension_t* extension,
      const cef_string_t* url,
      struct _cef_client_t** client,
      struct _cef_browser_settings_t* settings);

  ///
  /// Called when an extension API (e.g. chrome.tabs.create) requests creation
  /// of a new browser. |extension| and |browser| are the source of the API
  /// call. |active_browser| may optionally be specified via the windowId
  /// property or returned via the get_active_browser() callback and provides
  /// the default |client| and |settings| values for the new browser. |index| is
  /// the position value optionally specified via the index property. |url| is
  /// the URL that will be loaded in the browser. |active| is true (1) if the
  /// new browser should be active when opened.  To allow creation of the
  /// browser optionally modify |windowInfo|, |client| and |settings| and return
  /// false (0). To cancel creation of the browser return true (1). Successful
  /// creation will be indicated by a call to
  /// cef_life_span_handler_t::OnAfterCreated. Any modifications to |windowInfo|
  /// will be ignored if |active_browser| is wrapped in a cef_browser_view_t.
  ///
  int(CEF_CALLBACK* on_before_browser)(
      struct _cef_extension_handler_t* self,
      struct _cef_extension_t* extension,
      struct _cef_browser_t* browser,
      struct _cef_browser_t* active_browser,
      int index,
      const cef_string_t* url,
      int active,
      struct _cef_window_info_t* windowInfo,
      struct _cef_client_t** client,
      struct _cef_browser_settings_t* settings);

  ///
  /// Called when no tabId is specified to an extension API call that accepts a
  /// tabId parameter (e.g. chrome.tabs.*). |extension| and |browser| are the
  /// source of the API call. Return the browser that will be acted on by the
  /// API call or return NULL to act on |browser|. The returned browser must
  /// share the same cef_request_context_t as |browser|. Incognito browsers
  /// should not be considered unless the source extension has incognito access
  /// enabled, in which case |include_incognito| will be true (1).
  ///
  struct _cef_browser_t*(CEF_CALLBACK* get_active_browser)(
      struct _cef_extension_handler_t* self,
      struct _cef_extension_t* extension,
      struct _cef_browser_t* browser,
      int include_incognito);

  ///
  /// Called when the tabId associated with |target_browser| is specified to an
  /// extension API call that accepts a tabId parameter (e.g. chrome.tabs.*).
  /// |extension| and |browser| are the source of the API call. Return true (1)
  /// to allow access of false (0) to deny access. Access to incognito browsers
  /// should not be allowed unless the source extension has incognito access
  /// enabled, in which case |include_incognito| will be true (1).
  ///
  int(CEF_CALLBACK* can_access_browser)(struct _cef_extension_handler_t* self,
                                        struct _cef_extension_t* extension,
                                        struct _cef_browser_t* browser,
                                        int include_incognito,
                                        struct _cef_browser_t* target_browser);

  ///
  /// Called to retrieve an extension resource that would normally be loaded
  /// from disk (e.g. if a file parameter is specified to
  /// chrome.tabs.executeScript). |extension| and |browser| are the source of
  /// the resource request. |file| is the requested relative file path. To
  /// handle the resource request return true (1) and execute |callback| either
  /// synchronously or asynchronously. For the default behavior which reads the
  /// resource from the extension directory on disk return false (0).
  /// Localization substitutions will not be applied to resources handled via
  /// this function.
  ///
  int(CEF_CALLBACK* get_extension_resource)(
      struct _cef_extension_handler_t* self,
      struct _cef_extension_t* extension,
      struct _cef_browser_t* browser,
      const cef_string_t* file,
      struct _cef_get_extension_resource_callback_t* callback);
} cef_extension_handler_t;

#ifdef __cplusplus
}
#endif

#endif  // CEF_INCLUDE_CAPI_CEF_EXTENSION_HANDLER_CAPI_H_
