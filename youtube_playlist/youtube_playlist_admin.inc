<?php

/*
 * validate user input
 */

function youtube_playlist_admin_validate($form, &$form_state) {
    $youtube_playlist_gdata_playlist = $form_state['values']['youtube_playlist_gdata_playlist'];
    $youtube_playlist_records_per_page = $form_state['values']['youtube_playlist_records_per_page'];
    $youtube_playlist_cache_expiry = $form_state['values']['youtube_playlist_cache_expiry'];
    $youtube_playlist_gdata_playlist_search= $form_state['values']['youtube_playlist_gdata_playlist_search'];

    if (!valid_url($youtube_playlist_gdata_playlist, true)) {
        form_set_error('youtube_playlist_gdata_playlist', t('You must enter an valid Youtube playlist feed URL.'));
    }
    
     if (!valid_url($youtube_playlist_gdata_playlist_search, true)) {
        form_set_error('youtube_playlist_gdata_playlist_search', t('You must enter an valid Youtube playlist search URL.'));
    }

    if (!is_numeric($youtube_playlist_records_per_page)) {
        form_set_error('youtube_playlist_records_per_page', t('You must enter an integer for the default records per page.'));
    }
    if (!is_numeric($youtube_playlist_cache_expiry)) {
        form_set_error('youtube_playlist_cache_expiry', t('You must enter cache expiry in secs'));
    } else if ($youtube_playlist_cache_expiry<600){
         form_set_error('youtube_playlist_cache_expiry', t('You must cache at least for 10 minutes'));
    }
}

/*
 * admin settings form
 * 
 */

function youtube_playlist_admin() {
    $form = array();

    $form['youtube_playlist_gdata_playlist'] = array(
        '#type' => 'textfield',
        '#title' => t('Youtube Playlist feed url'),
        '#default_value' => variable_get('youtube_playlist_gdata_playlist', "http://gdata.youtube.com/feeds/api/playlists"),
        '#size' => 100,
        '#maxlength' => 255,
        '#description' => t("Youtube Playlist feed url"),
        '#required' => TRUE,
    );
    
     $form['youtube_playlist_gdata_playlist_search'] = array(
        '#type' => 'textfield',
        '#title' => t('Youtube Playlist search url'),
        '#default_value' => variable_get('youtube_playlist_gdata_playlist_search', "https://gdata.youtube.com/feeds/api/playlists/snippets"),
        '#size' => 100,
        '#maxlength' => 255,
        '#description' => t("Youtube Playlist search url"),
        '#required' => TRUE,
    );

    $form['youtube_playlist_records_per_page'] = array(
        '#type' => 'textfield',
        '#title' => t('Youtube Playlist default records per page'),
        '#default_value' => variable_get('youtube_playlist_records_per_page', 5),
        '#size' => 4,
        '#maxlength' => 3,
        '#description' => t("Youtube Playlist default records per page"),
        '#required' => TRUE,
    );
    
     $form['youtube_playlist_cache_expiry'] = array(
        '#type' => 'textfield',
        '#title' => t('Youtube Playlist default cache expiry in secs'),
        '#default_value' => variable_get('youtube_playlist_cache_expiry', 3600),
        '#size' => 10,
        '#maxlength' => 10,
        '#description' => t("Youtube Playlist default cache expiry in secs"),
        '#required' => TRUE,
    );

    return system_settings_form($form);
}

function youtube_playlist_autocomplete($string='') {
    $path = drupal_get_path('module', 'youtube_playlist');
    require_once "./$path/youtube.inc";
    $matches=array();
      $youtube_playlist_gdata_playlist_search = variable_get('youtube_playlist_gdata_playlist_search','https://gdata.youtube.com/feeds/api/playlists/snippets');
    try {
        $data = youtube_playlist_search_playlists($string,$youtube_playlist_gdata_playlist_search);
        if (isset($data->data->items)) {
            foreach ($data->data->items as $item) {
                $matches[$item->id] = $item->title;
            }
        }
    } catch (Exception $e) {
        //drupal_set_message($e->getMessage, 'error');
    }
    
    print drupal_json($matches);
    
}





    