<?php
/**
 *
 * @param type $palylist_id
 * @param type $feed_url
 * @param type $start_index
 * @param type $max_results
 * @param type $cache_time_secs
 * @return type 
 */
function youtube_playlist_get_youtube_playlist_feed($palylist_id,$feed_url='http://gdata.youtube.com/feeds/api/playlists',$start_index=1,$max_results=25,$cache_time_secs=3600) {
    
    $feed_url = "$feed_url/$palylist_id?v=2&alt=jsonc&start-index=$start_index&max-results=$max_results";
    $url_hash = md5($feed_url);
    $cache = cache_get($url_hash);

    if ($cache && (time() < $cache->expire)) {
        $data = $cache->data;
    } else {

        $content = @file_get_contents($feed_url);
        if ($content == false) {
            throw new Exception("error in fetching playlist feed data", 400);
        } else {
            $data = json_decode($content);
            cache_set($url_hash, $data, 'cache', time() + $cache_time_secs);
        }
    }
    return $data;
    
}




function youtube_playlist_get_youtube_user_playlists_feed($user_id,$feed_url='https://gdata.youtube.com/feeds/api/users',$start_index=1,$max_results=25,$cache_time_secs=3600) {
    
    $feed_url = "$feed_url/$user_id/playlists?v=2&alt=jsonc&start-index=$start_index&max-results=$max_results";
    $url_hash = md5($feed_url);

    $cache = cache_get($url_hash);

    if ($cache && (time() < $cache->expire)) {
        $data = $cache->data;
    } else {

        $content = @file_get_contents($feed_url);
        if ($content == false) {
            throw new Exception("error in fetching user playlists", 400);
        } else {
            $data = json_decode($content);
            cache_set($url_hash, $data, 'cache', time() + $cache_time_secs);
        }
    }
    return $data;
    
}

function youtube_playlist_search_playlists($string,$feed_url='https://gdata.youtube.com/feeds/api/playlists/snippets',$start_index=1,$max_results=25,$cache_time_secs=3600) {
    
    $feed_url="$feed_url?v=2&q=$string&alt=jsonc&start-index=$start_index&max-results=$max_results";
     $url_hash = md5($feed_url);

    $cache = cache_get($url_hash);

    if ($cache && (time() < $cache->expire)) {
        $data = $cache->data;
    } else {

        $content = @file_get_contents($feed_url);
        if ($content == false) {
            throw new Exception("error in fetching user playlists", 400);
        } else {
            $data = json_decode($content);
            cache_set($url_hash, $data, 'cache', time() + $cache_time_secs);
        }
    }
    return $data;
}

