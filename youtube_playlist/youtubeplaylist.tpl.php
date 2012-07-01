<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
//print_r($content->data);
//$youtubepager


foreach($content->data->items as $item) : 
?>
<a rel="prettyPhoto" href="<?php  print $item->video->player->default; ?>"><h2><?php print $item->video->title ?></h2></a>
<a rel="prettyPhoto" class="thumb"  href="<?php  print $item->video->player->default; ?>"><image src="<?php print $item->video->thumbnail->sqDefault ?>" /></a>
<div class="detail"><?php print $item->video->description ?></div>
<?php endforeach;

print $youtubepager;

?>
