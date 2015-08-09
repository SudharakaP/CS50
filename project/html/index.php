<?php

    // configuration
    require("../includes/config.php");
    
    foreach ($_POST as $book_id => $post)
    {        
        // insert book into my_books collection
        if ($post === "insert" && query("SELECT * FROM my_books WHERE book_id = ?", $book_id) == false)
        {
            query("INSERT INTO my_books (id, book_id) VALUES(?, ?)", $_SESSION["id"], $book_id);
        }
        
        // removes books from my_books collection
        if ($post === "remove")
        {
             query("DELETE FROM my_books WHERE book_id = ?", $book_id);
        }
    }
       
    $rows = query("SELECT book_id FROM my_books WHERE id = ?", $_SESSION["id"]);

    $books = [];
    foreach ($rows as $row)
    { 
        $books[] = query("SELECT * FROM books WHERE book_id = ?", $row["book_id"]);
    }
 
    // render profile
    render("profile.php", ["title" => "Profile", "books" => $books]);

?>
