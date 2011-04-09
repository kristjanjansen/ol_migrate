<?php

class OLArticleDBMigration extends Migration {
  public function __construct() {

    $this->dependencies = array('OLArticleCSV');

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
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'text')->arguments(array('format' => 'full_html'));
  
    // Unmapped source fields
     $this->addFieldMapping(NULL, 'supplement')->issueGroup('DNM');  
     $this->addFieldMapping(NULL, 'description')->issueGroup('DNM');  
     $this->addFieldMapping(NULL, 'author_alias')->issueGroup('DNM');  
     $this->addFieldMapping(NULL, 'publisher_id')->issueGroup('DNM');  
     $this->addFieldMapping(NULL, 'paywall')->issueGroup('DNM');  
 
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
      
}


class OLCommentDBMigration extends Migration {
  public function __construct() {

    $this->dependencies = array('OLArticleDB');
       
    parent::__construct();
 
    $query = db_select('ol_comment', 'ol_c')
             ->fields('ol_a', array('id', 'title', 'text', 'created', 'author_alias', 'email', 'show_email', 'subtopics_id', 'messages_id', 'ip', 'flame', 'step', 'answer'));

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
    $this->addFieldMapping('nid')->defaultValue(421892);
    $this->addFieldMapping('subject', 'title');
    $this->addFieldMapping('hostname', 'ip');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'created');
    $this->addFieldMapping('name', 'author_alias');
    $this->addFieldMapping('mail', 'email');
    $this->addFieldMapping('comment_body', 'text')->arguments(array('format' => 'full_html'));

    // Unmapped source fields
    $this->addFieldMapping(NULL, 'show_email')->issueGroup('DNM');  
    $this->addFieldMapping(NULL, 'subtopics_id')->issueGroup('DNM');  
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
  
}



