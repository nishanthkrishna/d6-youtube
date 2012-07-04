<?php



//==========================================//
// DEFINING A FORMATTER
//==========================================//

/**
 * Theme function for 'default'  field formatter.
 * 
 * $element['#item']: the sanitized $delta value for the item,
 * $element['#field_name']: the field name,
 * $element['#type_name']: the $node->type,
 * $element['#formatter']: the $formatter_name,
 * $element'#node']: the $node,
 * $element['#delta']: the delta of this item, like '0',
 * 
 */
function theme_youtube_playlist_formatter_default($element) {
    try {
        $element['#item']['safe'] = _load_youtube_palylist($element['#item']['safe'], $element['#item']['recordsperpage']);
    } catch (Exception $e) {
        drupal_set_message($e->getMessage, 'error');
    }
    return $element['#item']['safe'];
}

/**
 * Theme function for 'plain'  field formatter.
 */
function theme_youtube_playlist_formatter_plain($element) {
    return strip_tags($element['#item']['safe']);
}

function _load_youtube_palylist($id, $max_results='') {
    $path = drupal_get_path('module', 'youtube_playlist');
    require_once "./$path/youtube.inc";
    // init pagination
    if (!$max_results) {
        $max_results = variable_get('youtube_playlist_records_per_page', 5);
    }
    global $pager_page_array, $pager_total, $pager_total_items;
    $page = isset($_GET['page']) ? $_GET['page'] : '';
    if (is_array($pager_total_items)) {
        $element = count($pager_total_items);
    } else {
        $element = 0;
    }

    $pager_page_array = explode(',', $page);

    $start_index = ($pager_page_array[$element]) * $max_results + 1;
    $gdat_base_url = variable_get('youtube_playlist_gdata_playlist', "http://gdata.youtube.com/feeds/api/playlists");
    try {
        $data = youtube_playlist_get_youtube_playlist_feed($id, $gdat_base_url, $start_index, $max_results);
        if ($data) {
            $pager_total_items[$element] = $data->data->totalItems;
            $pager_total[$element] = ceil($pager_total_items[$element] / $max_results);
            $pager_page_array[$element] = max(0, min((int) $pager_page_array[$element], ((int) $pager_total[$element]) - 1));
            $pager = theme('pager', array(), $max_results, $element);
            return theme(array("youtubeplaylist"), $data, $pager);
        }
    } catch (Exception $e) {
    
        drupal_set_message($e->getMessage, 'error');
    }
}

