<?php

class OLArticleDBMigration extends Migration {
  public function __construct() {

    $this->dependencies = array('OLImageCSV');

    parent::__construct();
    
    $query = db_select('ol_article', 'ol_a')
             ->fields('ol_a', array('id', 'pubdate', 'title', 'supplement', 'description', 'text', 'author_alias', 'publisher_id', 'paywall'));

    $this->source = new MigrateSourceSQL($query);
             
    $this->destination = new MigrateDestinationNode('article');
 
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'id' => array('type' => 'int',
                        'unsigned' => TRUE,
                        'not null' => TRUE,
                        )
        ),
        MigrateDestinationNode::getKeySchema()
      );
    
    $this->addFieldMapping('nid', 'id');
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('created', 'pubdate');
    $this->addFieldMapping('changed', 'pubdate');
    $this->addFieldMapping('title', 'title_stripped');
    $this->addFieldMapping('field_title', 'title')->arguments(array('format' => 'full_html'));
    $this->addFieldMapping('supplement', 'supplement')->arguments(array('format' => 'full_html'));
    $this->addFieldMapping('field_description', 'description')->arguments(array('format' => 'full_html'));
    $this->addFieldMapping('field_text', 'text')->arguments(array('format' => 'full_html'));
    $this->addFieldMapping('field_publisher', 'publisher_id');
    $this->addFieldMapping('field_paywall', 'paywall');

    if (module_exists('node_reference')) {
      $this->addFieldMapping('field_related_article', 'related_article')
      ->separator('|');
    }

    $associated_file_arguments = MigrateFileFieldHandler::arguments(drupal_get_path('module', 'ol_migrate') . '/data/' , 'file_copy', FILE_EXISTS_RENAME, NULL, 2, 1, NULL, NULL, ';');
    $this->addFieldMapping('field_image', 'images')
      ->separator('|')
      ->arguments($associated_file_arguments);

          
    // Unmapped source fields
     $this->addFieldMapping(NULL, 'author_alias')->issueGroup('DNM');  
 
    // Unmapped destination fields
     $this->addFieldMapping('vid')->issueGroup('DNM');  
     $this->addFieldMapping('type')->issueGroup('DNM');  
     $this->addFieldMapping('language')->issueGroup('DNM');  
     $this->addFieldMapping('uid')->issueGroup('DNM');  
     $this->addFieldMapping('status')->issueGroup('DNM');  
     $this->addFieldMapping('comment')->issueGroup('DNM');
     $this->addFieldMapping('promote')->issueGroup('DNM');
     $this->addFieldMapping('sticky')->issueGroup('DNM');
     $this->addFieldMapping('tnid')->issueGroup('DNM');
     $this->addFieldMapping('translate')->issueGroup('DNM');
  }

  public function prepareRow($current_row) {
  
    // Title mapping does not seem to accept text format parameter
    // so we need to create a temporary value 
    $current_row->title_stripped = strip_tags($current_row->title);
    
    // Get related images
    $images = array();
    $result = db_select('ol_image', 'ol_i')
      ->fields('ol_i', array('id', 'article_id', 'caption', 'alt', 'url', 'author_alias', 'contenttype_id', 'imagetype_id', 'ordering', 'x_width', 'x_height'))
      ->condition('article_id', $current_row->id)
      ->execute();
    if ($result) {
      foreach ($result as $row) {      
        $images[] = 'x-' . basename($row->url) . ';' . $row->caption . '(' . ucwords(strtolower($row->author_alias)). ');' . $row->alt;
      }    
      $current_row->images = implode('|', $images);
    }
  
    // Get related articles
    $articles = array();
      $result = db_select('ol_related_article', 'ol_r_a')
        ->fields('ol_r_a', array('id', 'article_id', 'related_article_id', 'front'))
        ->condition('article_id', $current_row->id)
        ->execute();
      if ($result) {
        foreach ($result as $row) {      
          $articles[] = $row->related_article_id;
        }    
        $current_row->related_article = implode('|', $articles);
      }
  
  
  }

}


class OLCommentDBMigration extends Migration {
  public function __construct() {

    $this->dependencies = array('OLArticleDB');
       
    parent::__construct();
 
    $query = db_select('ol_comment', 'ol_c')
             ->fields('ol_c', array('id', 'title', 'text', 'created', 'author_alias', 'email', 'show_email', 'subtopics_id', 'messages_id', 'ip', 'flame', 'step', 'answer'));

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationComment('comment_node_article');
 
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'id' => array('type' => 'int',
                        'unsigned' => TRUE,
                        'not null' => TRUE,
                        )
        ),
        MigrateDestinationComment::getKeySchema()
      );
 
//  $this->addFieldMapping('cid', 'id');  
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('subject', 'title');
    $this->addFieldMapping('hostname', 'ip');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'created');
    $this->addFieldMapping('name', 'author_alias');
    $this->addFieldMapping('mail', 'email');
    $this->addFieldMapping('comment_body', 'text')->arguments(array('format' => 'full_html'));

    // Unmapped source fields
    $this->addFieldMapping(NULL, 'show_email')->issueGroup('DNM');  
    // $this->addFieldMapping(NULL, 'subtopics_id')->issueGroup('DNM');  
    $this->addFieldMapping(NULL, 'messages_id')->issueGroup('DNM');  
    $this->addFieldMapping(NULL, 'flame')->issueGroup('DNM');  
    $this->addFieldMapping(NULL, 'step')->issueGroup('DNM');  
    $this->addFieldMapping(NULL, 'answer')->issueGroup('DNM');  

    // Unmapped destination fields
    $this->addFieldMapping('pid')->issueGroup('DNM');  
    $this->addFieldMapping('uid')->issueGroup('DNM');  
    $this->addFieldMapping('status')->issueGroup('DNM');  
    $this->addFieldMapping('thread')->issueGroup('DNM');  
    $this->addFieldMapping('homepage')->issueGroup('DNM');  
    $this->addFieldMapping('language')->issueGroup('DNM');  
    
  }

  public function prepareRow($current_row) {
    // Get article ID for comment
    $result = db_select('ol_forum_subtopics', 'ol_f_s')
      ->fields('ol_f_s', array('article_id'))
      ->condition('id', $current_row->subtopics_id)
      ->execute();
    if ($result) {
      foreach ($result as $row) {      
        $current_row->nid = $row->article_id;
      }
    }
  }  


}

class OLUserDBMigration extends Migration {

  public static $authors = array();

  public function __construct() {
    
    $this->dependencies = array('OLArticleCSV');

    parent::__construct();
    
    $result = db_select('ol_article', 'ol_a')
             ->fields('ol_a', array('author_alias'))
             ->distinct()
             ->execute();
    if ($result) {
      foreach ($result as $row) {      
        print_r($row->author_alias);
      }
    }
    
    $query = db_select('ol_article', 'ol_a')
             ->fields('ol_a', array('author_alias', 'id'))
             ->condition('author_alias', '', '<>');

    $this->source = new MigrateSourceSQL($query);
             
    $this->destination = new MigrateDestinationUser();
 
    $this->map = new MigrateSQLMap($this->machineName,
        array(

         'id' => array(
           'type' => 'int',
           'unsigned' => TRUE,
           'not null' => TRUE,
          ),

        ),
        MigrateDestinationUser::getKeySchema()
      );
        
    $this->addFieldMapping('name', 'author_alias')->dedupe('users','name')->defaultValue(NULL);
  }
    
  public function prepareRow($current_row) {
    $current_row->author_alias = ol_migrate_author_clean($current_row->author_alias);
    if (in_array($current_row->author_alias, OLUserDBMigration::$authors)) {
      return FALSE;
    } else {
      OLUserDBMigration::$authors[] = $current_row->author_alias;
      
      return TRUE;
    }
  }

}

function ol_migrate_author_clean($author_alias) {
  if ($author_alias) {
    $author_parts = explode(' ', $author_alias);
    array_walk($author_parts, 'trim');
  //  print_r($author_parts);
    if ($author_parts[0] == 'Toimetas') {
      unset($author_parts[0]);
    }
    return implode(' ', $author_parts);
  }
}
