<?php

    // configuration
    require("../includes/config.php"); 

    // if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check whether a symbol is provided by user
        if (!empty($_POST["course_code"]))
        {
            // converts alphabetic characters in course code to uppercase
            $symbol = strtoupper ($_POST["course_code"]);
           
            $rows = query("SELECT * FROM books WHERE course = ?", $symbol);
            
            // check whether books are found
            if (empty($rows))
            {
                apologize("No books found.");  
            }
            else
            {
                render("book_list.php", ["title" => "Books", "books" => $rows]);
            }
          
        }
        else
        {
            apologize("You must provide a course code.");
        }
    }
    else
    {
        // else render form
        render("search_form.php", ["title" => "Search"]);
    }
   
?>
