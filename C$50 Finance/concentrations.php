<?php

    $file_array = file("concentrations.txt");
    if ($file_array === false)
        exit;
    
    echo '<select name="concentration">';
    echo '<option></option>';
    
    foreach($file_array as $key => $line)
        echo "<option value=" . ($key+1) . ">$line</option>";
        
    echo '</select>';
    
?>
