<?php

    // configuration
    require("../includes/config.php");
    
    $rows = query("SELECT transaction, date_time, symbol, shares, price FROM history 
                 WHERE id = ?", $_SESSION["id"]);
                 
    // render history_page
    render("history_page.php", ["title" => "History", "rows" => $rows]);

?>
