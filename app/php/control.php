<?php include "includes/auth_guard.php"; ?>

<!DOCTYPE html>

<html lang="pt-br">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <title>RAISS</title>
    <link href="../css/controle.css" rel="stylesheet">
  </head>

  <body>
    <header class="header">
      <h3 class="logo">INTERFACE DE CONTROLE</h3>
      <nav class="navbar">
        <?php echo "Logado como $logado"; ?>
        <a href="management.php">GERENCIAR USUÁRIOS</a>
        &bull;
        <a href="includes/auth_logout.php">SAIR</a>
      </nav>
    </header>

    <section class="container">
      <div class="control">
        <span class="column">
          <a class="link" href="commands/reseta.php" target="_blank">RESET</a>
          <a class="link" href="commands/garra-1.php" target="_blank">Garra Aberta</a>
          <a class="link" href="commands/garra-2.php" target="_blank">Semi Aberta</a>
          <a class="link" href="commands/garra-3.php" target="_blank">Garra Fechada</a>
        </span>
        <span class="column">
          <a class="link" href="commands/avanco-1.php" target="_blank">Avanço 50º</a>
          <a class="link" href="commands/avanco-2.php" target="_blank">Avanço 100º</a>
          <a class="link" href="commands/avanco-3.php" target="_blank">Avanço 150º</a>
          <a class="link" href="commands/avanco-4.php" target="_blank">Avanço 200º</a>
        </span>
      </div>

      <iframe id="iframe" class="iframe" src="http://192.168.15.3:8080/jsfs.html"></iframe>

      <div class="control">
        <span class="column">
          <a class="link" href="commands/mergulho-1.php" target="_blank">Mergulho 0º</a>
          <a class="link" href="commands/mergulho-2.php" target="_blank">Mergulho 25º</a>
          <a class="link" href="commands/mergulho-3.php" target="_blank">Mergulho 50º</a>
          <a class="link" href="commands/mergulho-4.php" target="_blank">Mergulho 75º</a>
          <a class="link" href="commands/mergulho-5.php" target="_blank">Mergulho 100º</a>
        </span>
        <span class="column">
          <a class="link" href="commands/base-1.php" target="_blank">Base 0º</a>
          <a class="link" href="commands/base-2.php" target="_blank">Base 45º</a>
          <a class="link" href="commands/base-3.php" target="_blank">Base 90º</a>
          <a class="link" href="commands/base-4.php" target="_blank">Base 135º</a>
          <a class="link" href="commands/base-5.php" target="_blank">Base 180º</a>
        </span>
      </div>
    </section>

    <div class="reference">
      <span>
        <h3>GARRA</h3>
        <img src="../img/garra.png">
      </span>
      <span>
        <h3>AVANÇO</h3>
        <img src="../img/avanco.png">
      </span>
      <span>
        <h3>MERGULHO</h3>
        <img src="../img/mergulho.png">
      </span>
      <span>
        <h3>BASE</h3>
        <img src="../img/base.png">
      </span>
    </div>

    <footer class="footer">
      <span>&copy;2016 - RAISS</span>
      <nav class="navbar">
        <?php echo "Logado como $loggedUsername"; ?>
        <a href="management.php">GERENCIAR USUÁRIOS</a>
        &bull;
        <a href="includes/auth_logout.php">SAIR</a>
      </nav>
    </footer>
  </body>
</html>
