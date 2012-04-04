<?php

module_load_include('inc', 'incrwd', 'incrwd_utils');

class IncrwdApi {

  // This always gets incremented by 1.
  var $api_version = '2';

  function IncrwdApi($site_id, $secret_key, $api_url) {
    $this->site_id = $site_id;
    $this->secret_key = $secret_key;
    $this->api_url = $api_url;
  }

  function approved_comment_left($comment_id) {
    $this->call("approved_comment", 
                array("comment_id" => $comment_id,
                      "remote_cookie" => $_COOKIE["__ic"]));
  }

  /**
   * Makes a call to an Incrwd API method.
   *
   * @param $method
   *   The Incrwd API method to call.
   * @param $args
   *   An associative array of arguments to be passed.
   */
  function call($method, $args=array()) {
    if (!($this->site_id)) {
      return -1;
    }
    $url = $this->api_url . $method . '/';
    $args['api_version'] = $this->api_version;
    $real_args = array(
      "site_id" => $this->site_id,
      "args" => incrwd_encode_arr($args));
    $response = drupal_http_request(
      $url,
      array(
        'method' => 'POST',
        'data' => http_build_query($real_args)));
    if ($response->code != 200) {
      return -1;
    } else {
      return $response->data;
    }
  }
}

?>
