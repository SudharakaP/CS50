<?php

    // configuration
    require("../includes/config.php");
    
    $rows = query("SELECT shares, symbol FROM portfolios WHERE id = ?", $_SESSION["id"]);
    $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash_bal = number_format($cash[0]["cash"], 2);
    
    $positions = [];
    
    // helps to create portfolio table
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => number_format($stock["price"], 2),
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "total" => number_format($stock["price"] * $row["shares"], 2)
            ];
        }
    }
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, 
                                                        "cash_bal" => $cash_bal]);

?>
