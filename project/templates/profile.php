<ul class="nav nav-pills">
    <li><a href="search.php"><strong>Search Ebooks</strong></a></li>
    <li><a href="password.php"><strong>Change Password</strong></a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>

<form action="index.php" method="post">

    <table class="table table-striped">
        <thead>
            <tr>
                <th>Ebook Name</th>
                <th>Author</th>
                <th>Course</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($books as $book): ?>
            <tr>
                <td><?= "<a target=\"_blank\" href ='{$book[0]["link"]}'>{$book[0]["name"]}</a>"?></td>
                <td><?= $book[0]["author"] ?></td>
                <td><?= $book[0]["course"] ?></td>
                <td><?= '<input type="checkbox" name="'.$book[0]["book_id"].'" value="remove">' ?>
            </tr>
            <? endforeach ?>
       </tbody>
    </table>
    <button class="btn btn-primary" type="submit">Remove</button>    
</form>
