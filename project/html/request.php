<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // checks for validity of inputs
        if (empty($_POST["full_name"]))
        {
            apologize("You must provide your full name.");
        }
        else if (empty($_POST["department"]))
        {
            apologize("You must provide your affiliated department.");
        }
        else if (empty($_POST["student_number"]))
        {
            apologize("You must provide your student number.");
        }
        else if (empty($_POST["email"]))
        {
            apologize("You must provide your email.");
        }
        else if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match.");
        }
        
        // checks for validity of email
        if (!filter_var($_POST["email"], FILTER_VALIDATE_EMAIL))
        {
            apologize("Email not valid.");
        }        
        
        //TODO
                        
        // redirect to index.php
        render("request_success.php", ["title" => "Success"]);
                   
    }
    else
    {
        // else render form
        render("request_form.php", ["title" => "Request"]);
    }

?>
