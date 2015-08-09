<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["current_password"]))
        {
            apologize("You must provide your current password.");
        }
        else if (empty($_POST["new_password"]))
        {
            apologize("You must provide a new password.");
        }
        else if (empty($_POST["new_password_confirm"]))
        {
            apologize("You must confirm new password.");
        }
        else if ($_POST["new_password"] != $_POST["new_password_confirm"])
        {
            apologize("Passwords do not match.");
        }

        // query database for user
        $row = query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);

        // checks whether the current password is correct
        if (crypt($_POST["current_password"], $row[0]["hash"]) == $row[0]["hash"])
        {
            // change password
            query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["new_password"]), $_SESSION["id"]);
            
            render("password_change.php", ["title" => "Password Change"]);
        }        
        else 
        {
            apologize("Invalid Password.");
        }
    }
    else
    {    
        // render pasword_form
        render("password_form.php", ["title" => "Change Password"]);
    }
      
?>
