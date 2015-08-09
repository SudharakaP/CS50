<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        // checks for valid username, passwords
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match.");
        }
        
        // inserts values into database                
        if (query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", 
                $_POST["username"], crypt($_POST["password"])))
        {        
            apologize("Please enter a different username and/or password.");        
        }
        
        $rows = query("SELECT LAST_INSERT_ID() AS id"); 
       
        // remember that user's now logged in by storing user's ID in session
        $_SESSION["id"] = $rows[0]["id"];
        
        // redirect to index.php
        redirect("/");
                   
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
