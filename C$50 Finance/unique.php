<?php

    if (count($argv) != 2)
        exit;

    $file_array = file($argv["1"]);
    if ($file_array === false)
        exit;
    
    sort($file_array);  
    
    foreach($file_array as $line)
        print($line);

?>
