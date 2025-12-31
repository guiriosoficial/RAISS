<?php include 'inclusoes/conta.php'; ?>

<!DOCTYPE html>

<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <title>RAISS</title>
    <link href="../css/registro.css" rel="stylesheet">
  </head>

  <body>
    <div class="container">
      <header class="header">
        <h3 class="logo">CONTROLE DE USUÁRIOS</h3>
        <nav class="navbar">
          <span>
            <?php echo "Logado com $logado"; ?>
          </span>
          <br>
          <a href="controle.php">VOLTAR</a>
          &bull;
          <a href="inclusoes/logoff.php">SAIR</a>
        </nav>
      </header>

      <main class="main">
        <section class="section">
          <h3 class="title">USUÁRIOS REGISTRADOS</h3>
          <?php TabelaUsuarios($link, $tabela); ?>
        </section>

        <section class="section">
          <h3 class="title">ADICIONAR USUÁRIO</h3>
          <form class="form" action="<?php echo $self; ?>" method="post">
            <div class="add-row">
              <label for="login">Login:</label>
              <input id="login" type="text" name="login_a"><?php echo $login_err; ?>
            </div>
            <div class="add-row">
              <label for="password">Senha:</label>
              <input id="password" type="password" name="senha"><?php echo $senha_err; ?>
            </div>
            <div class="add-row">
              <label for="pass-confirm">Confirmação:</label>
              <input id="pass-confirm" type="password" name="confirm"><?php echo $confirm_err; ?>
            </div>
            <button type="submit">Adicionar</button>
          </form>
        </section>

        <section class="section">
          <h3 class="title">REMOVER USUÁRIOS</h3>
          <form class="form" action="<?php echo $self; ?>" method="post">
            <div class="remove-row">
              <label for="remove">Login do Usuário:</label>
              <input id="remove" type="text" name="login_d"><?php echo $login_derr; ?>
            </div>
            <button type="submit">Remover</button>
          </form>
        </section>

        <section class="section">
          <h3 class="title">CONFIGURAÇÕES DE USUÁRIO</h3>
          <form class="form" action="<?php echo $self; ?>" method="post">
            <label for="edit">Login do Usuário:</label>
            <input id="edit" type="text" name="login">
            <div class="edit-row">
              <label>Tipo de Usuário:</label>
              <span>
              <input id="comum" type="radio" name="nivel" value="1" checked>
              <label for="comum">Usuário Comum</label>
            </span>
              <span>
              <input id="adm" type="radio" name="nivel" value="2">
              <label for="adm">Admnistrador</label>
            </span>
            </div>
            <div class="edit-row">
              <label>Status:</label>
              <span>
              <input id="ativo" type="radio" name="ativa" value="1" checked>
              <label for="ativo">Ativo</label>
            </span>
              <span>
              <input id="inativo" type="radio" name="ativa" value="0">
              <label for="inativo">Inativo</label>
            </span>
            </div>
            <button type="submit">Alterar</button>
          </form>
        </section>
      </main>

      <footer class="footer">
        <span>&copy;2016 - RAISS</span>
        <nav class="navbar">
          <span>
            <?php echo "Logado como $logado"; ?>
          </span>
          <br>
          <a href="controle.php">VOLTAR</a>
          &bull;
          <a href="inclusoes/logoff.php">SAIR</a>
        </nav>
      </footer>
    </div>
  </body>
</html>