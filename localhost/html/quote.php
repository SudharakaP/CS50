<?php

    // configuration
    require("../includes/config.php"); 

    // if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check whether a symbol is provided by user
        if (!empty($_POST["symbol"]))
        {
            $stock = lookup($_POST["symbol"]);
            
            // check whether given symbol was found
            if ($stock !== false)
            {
                $stock["price"] = number_format($stock["price"], 2);
                render("quote_display.php", ["title" => "Quote", "stock" => $stock]);
            }
            else
            {
                apologize("Symbol not found.");
            }
        }
        else
        {
            apologize("You must provide a symbol.");
        }
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }
   
?>
