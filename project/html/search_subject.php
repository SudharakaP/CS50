<?php

    // configuration
    require("../includes/config.php"); 
    
    // checks whether books exist for the given subject
    $rows = query("SELECT * FROM books WHERE subject_code = ?", $_POST["button"]);
    
    if (!empty($rows))
    {
        render("book_list.php", ["title" => "Books", "books" => $rows]);
    }
    else
    {
        apologize("No books found.");
    }

?>
