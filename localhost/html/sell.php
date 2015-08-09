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
             
             // select row from portfolios table for future reference
             $shares = query("SELECT shares FROM portfolios WHERE id = {$_SESSION["id"]} 
                                            AND symbol = '{$_POST["symbol"]}'");
             
             // delete corresponding row from portfolios table
             query("DELETE FROM portfolios WHERE id = {$_SESSION["id"]} 
                                            AND symbol = '{$_POST["symbol"]}'");
             
             // update users cash                       
             $rows = query("UPDATE users SET cash = (cash +  {$shares[0]["shares"]} * {$stock["price"]}) 
                                                WHERE id = {$_SESSION["id"]}");
                                                
             // update history table
             query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES({$_SESSION["id"]}, 
                    'SELL', '{$_POST["symbol"]}', {$shares[0]["shares"]},{$stock["price"]})");
             
             redirect("/");
        }
        else
        {
            apologize("You must select a stock to sell.");
        }
    }
    else
    {
        // render sell_form
        $rows = query("SELECT symbol FROM portfolios WHERE id = ?", $_SESSION["id"]);
        render("sell_form.php", ["title" => "Sell", "rows" => $rows]);
    }

?>
