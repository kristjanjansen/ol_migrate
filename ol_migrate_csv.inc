<?php

class OLArticleCSVMigration extends Migration {

  public function __construct() {
    parent::__construct();
    $destination_key = array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
    );
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'ol_migrate') . '/data/ol_article.csv', $this->csvcolumns(), array('delimiter' => ';'));
    $this->destination = new MigrateDestinationTableCopy('ol_article', $destination_key);

    $this->map = new MigrateSQLMap($this->machineName,
    array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
       )
    ),
    $destination_key
    );
  }

  function csvcolumns() {
    // id;pubdate;title;supplement;description;text;author_alias;publisher_id;paywall
    $columns[0] = array('id', '');
    $columns[1] = array('pubdate', '');
    $columns[2] = array('title', '');
    $columns[3] = array('supplement', '');
    $columns[4] = array('description', '');
    $columns[5] = array('text', '');
    $columns[6] = array('author_alias', '');
    $columns[7] = array('publisher_id', '');
    $columns[8] = array('paywall', '');
    return $columns;
  }
}


class OLCommentCSVMigration extends Migration {
  public function __construct() {

    $this->dependencies = array('OLArticleCSV');

    parent::__construct();
    $destination_key = array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
    );
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'ol_migrate') . '/data/ol_comment.csv', $this->csvcolumns(), array('delimiter' => ';'));
    $this->destination = new MigrateDestinationTableCopy('ol_comment', $destination_key);

    $this->map = new MigrateSQLMap($this->machineName,
    array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
       )
    ),
    $destination_key
    );
  }

  function csvcolumns() {
    // id;title;text;created;author_alias;email;show_email;subtopics_id;messages_id;ip;flame;step;answer
    $columns[0] = array('id', '');
    $columns[1] = array('title', '');
    $columns[2] = array('text', '');
    $columns[3] = array('created', '');
    $columns[4] = array('author_alias', '');
    $columns[5] = array('email', '');
    $columns[6] = array('show_email', '');
    $columns[7] = array('subtopics_id', '');
    $columns[8] = array('messages_id', '');
    $columns[9] = array('ip', '');
    $columns[10] = array('flame', '');
    $columns[11] = array('step', '');
    $columns[12] = array('answer', '');
    return $columns;
  }
}

class OLImageCSVMigration extends Migration {
  public function __construct() {

    $this->dependencies = array('OLArticleCSV');

    parent::__construct();
    $destination_key = array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
    );
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'ol_migrate') . '/data/ol_image.csv', $this->csvcolumns(), array('delimiter' => ';'));
    $this->destination = new MigrateDestinationTableCopy('ol_image', $destination_key);

    $this->map = new MigrateSQLMap($this->machineName,
    array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
       )
    ),
    $destination_key
    );
  }

  function csvcolumns() {
    // id;article_id;caption;alt;url;author_alias;contenttype_id;imagetype_id;ordering;x_width;x_height
    $columns[0] = array('id', '');
    $columns[1] = array('article_id', '');
    $columns[2] = array('caption', '');
    $columns[3] = array('alt', '');
    $columns[4] = array('url', '');
    $columns[5] = array('author_alias', '');
    $columns[6] = array('contenttype_id', '');
    $columns[7] = array('imagetype_id', '');
    $columns[8] = array('ordering', '');
    $columns[9] = array('x_width', '');
    $columns[10] = array('x_height', '');
    return $columns;
  }
}

class OLRelatedArticleCSVMigration extends Migration {
  public function __construct() {

    parent::__construct();
    $destination_key = array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
    );
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'ol_migrate') . '/data/ol_related_article.csv', $this->csvcolumns(), array('delimiter' => ';'));
    $this->destination = new MigrateDestinationTableCopy('ol_related_article', $destination_key);

    $this->map = new MigrateSQLMap($this->machineName,
    array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
       ),
    ),
    $destination_key
    );
  }

  function csvcolumns() {
    $columns[0] = array('id', '');
    $columns[1] = array('article_id', '');
    $columns[2] = array('related_article_id', '');
    $columns[3] = array('front', '');
    return $columns;
  }
}

class OLArticleCommentCSVMigration extends Migration {
  public function __construct() {

    parent::__construct();
    $destination_key = array(
      'comment_id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
    );
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'ol_migrate') . '/data/ol_article_comment.csv', $this->csvcolumns(), array('delimiter' => ';'));
    $this->destination = new MigrateDestinationTableCopy('ol_article_comment', $destination_key);

    $this->map = new MigrateSQLMap($this->machineName,
    array(
      'comment_id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
       ),
    ),
    $destination_key
    );
  }

  function csvcolumns() {
    $columns[0] = array('article_id', '');
    $columns[1] = array('comment_id', '');
    return $columns;
  }
}


class OLForumSubtopicsCSVMigration extends Migration {

  public function __construct() {
    parent::__construct();
    $destination_key = array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
    );
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'ol_migrate') . '/data/ol_forum_subtopics.csv', $this->csvcolumns(), array('delimiter' => ';'));
    $this->destination = new MigrateDestinationTableCopy('ol_forum_subtopics', $destination_key);

    $this->map = new MigrateSQLMap($this->machineName,
    array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
       )
    ),
    $destination_key
    );
  }


function csvcolumns() {
    $columns[0] = array('id', '');
    $columns[1] = array('title', '');
    $columns[2] = array('description', '');
    $columns[3] = array('author_alias', '');
    $columns[4] = array('created_by', '');
    $columns[5] = array('created', '');
    $columns[6] = array('last_comment', '');
    $columns[7] = array('messages', '');
    $columns[8] = array('topictype', '');
    $columns[9] = array('article_id', '');
    $columns[10] = array('maintopics_id', '');
    return $columns;
  }
}