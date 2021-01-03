# MySQL-Front Dump 2.5
#
# Host: localhost   Database: sppix
# --------------------------------------------------------
# Server version 3.23.49-nt


#
# Table structure for table 'cat'
#

CREATE TABLE cat (
  cat_id varchar(32) NOT NULL default '0',
  name varchar(16) NOT NULL default '',
  sex char(1) default NULL,
  weight float default NULL,
  PRIMARY KEY  (cat_id)
) TYPE=MyISAM;



#
# Dumping data for table 'cat'
#

INSERT INTO cat VALUES("0001", "С��", "F", "7.4");
INSERT INTO cat VALUES("0002", "С��", "M", "7.4");


#
# Table structure for table 'gl_adminids'
#

CREATE TABLE gl_adminids (
  adminID varchar(64) NOT NULL default '',
  password varchar(64) NOT NULL default '',
  PRIMARY KEY  (adminID)
) TYPE=MyISAM;



#
# Dumping data for table 'gl_adminids'
#

INSERT INTO gl_adminids VALUES("admin", "admin");


#
# Table structure for table 'gl_app_tools'
#

CREATE TABLE gl_app_tools (
  appID varchar(64) NOT NULL default '',
  description varchar(254) NOT NULL default '',
  PRIMARY KEY  (appID)
) TYPE=MyISAM;



#
# Dumping data for table 'gl_app_tools'
#

INSERT INTO gl_app_tools VALUES("usermgt", "�û�������");
INSERT INTO gl_app_tools VALUES("datamgt", "���ݹ�����");
INSERT INTO gl_app_tools VALUES("servermgt", "���������");


#
# Table structure for table 'gl_role_rights'
#

CREATE TABLE gl_role_rights (
  node varchar(32) NOT NULL default '',
  role varchar(128) NOT NULL default '',
  target varchar(254) NOT NULL default '',
  permit int(11) default '0',
  right_r int(11) default '0',
  right_w int(11) default '0',
  right_d int(11) default '0',
  PRIMARY KEY  (node,role,target)
) TYPE=MyISAM;



#
# Dumping data for table 'gl_role_rights'
#

INSERT INTO gl_role_rights VALUES("spp", "mgt", "spp:mgt", "1", "1", "1", "1");
INSERT INTO gl_role_rights VALUES("spp", "mgt", "spp", "1", "1", "1", "1");
INSERT INTO gl_role_rights VALUES("spp", "role02", "spp:biz:stru", "1", "1", "1", "0");
INSERT INTO gl_role_rights VALUES("spp", "role02", "spp:biz:stru:kgjb_slscclqk", "1", "1", "1", "1");
INSERT INTO gl_role_rights VALUES("spp", "role02", "spp:mgt:auth", "1", "1", "0", "0");
INSERT INTO gl_role_rights VALUES("spp", "role02", "spp", "1", "1", "0", "0");
INSERT INTO gl_role_rights VALUES("spp", "role02", "spp:mgt", "1", "0", "0", "0");
INSERT INTO gl_role_rights VALUES("spp", "role01", "spp:biz", "1", "1", "1", "0");
INSERT INTO gl_role_rights VALUES("spp", "role01", "spp:mgt:auth", "1", "1", "0", "0");
INSERT INTO gl_role_rights VALUES("spp", "role01", "spp:mgt", "1", "0", "0", "0");
INSERT INTO gl_role_rights VALUES("spp", "role01", "spp", "1", "1", "0", "0");
INSERT INTO gl_role_rights VALUES("shanghai", "role0", "shanghai", "1", "1", "1", "1");
INSERT INTO gl_role_rights VALUES("shanghai", "role1", "shanghai", "0", "1", "0", "0");
INSERT INTO gl_role_rights VALUES("shanghai", "role2", "shanghai", "0", "1", "0", "0");
INSERT INTO gl_role_rights VALUES("shanghai", "role1", "shanghai:mgt", "0", "0", "0", "0");
INSERT INTO gl_role_rights VALUES("shanghai", "role2", "shanghai:mgt", "0", "0", "0", "0");
INSERT INTO gl_role_rights VALUES("shanghai", "role1", "shanghai:biz:stru:kgjb_slscclqk", "0", "1", "1", "1");
INSERT INTO gl_role_rights VALUES("shanghai", "role1", "shanghai:biz:stru:kgjb_slscclqk:jcy001wysbh1001", "0", "0", "0", "0");
INSERT INTO gl_role_rights VALUES("shanghai", "role1", "shanghai:biz:stru:xsss_slscqk", "0", "0", "0", "0");
INSERT INTO gl_role_rights VALUES("shanghai", "role2", "shanghai:biz:stru:xspc_scblqk", "0", "0", "0", "0");


#
# Table structure for table 'gl_roles'
#

CREATE TABLE gl_roles (
  role varchar(128) NOT NULL default '',
  description varchar(254) NOT NULL default '',
  PRIMARY KEY  (role)
) TYPE=MyISAM;



#
# Dumping data for table 'gl_roles'
#

INSERT INTO gl_roles VALUES("role01", "��ɫ1");
INSERT INTO gl_roles VALUES("role02", "��ɫ2");
INSERT INTO gl_roles VALUES("mgt", "ϵͳ����Ա");
INSERT INTO gl_roles VALUES("role0", "����Ա��Managers��");
INSERT INTO gl_roles VALUES("role1", "�����û�");
INSERT INTO gl_roles VALUES("role2", "�ⵥλ�û�");
INSERT INTO gl_roles VALUES("spp:mgt", "");
INSERT INTO gl_roles VALUES("spp:biz:stru", "");
INSERT INTO gl_roles VALUES("spp:biz", "");
INSERT INTO gl_roles VALUES("shanghai", "");


#
# Table structure for table 'gl_user_apps'
#

CREATE TABLE gl_user_apps (
  uid varchar(64) NOT NULL default '',
  appID varchar(64) NOT NULL default '',
  description varchar(254) NOT NULL default '',
  PRIMARY KEY  (uid,appID)
) TYPE=MyISAM;



#
# Dumping data for table 'gl_user_apps'
#

INSERT INTO gl_user_apps VALUES("user01", "usermgt", "�û�������");
INSERT INTO gl_user_apps VALUES("user01", "datamgt", "���ݹ�����");
INSERT INTO gl_user_apps VALUES("user02", "datamgt", "���ݹ�����");
INSERT INTO gl_user_apps VALUES("user02", "servermgt", "���������");
INSERT INTO gl_user_apps VALUES("manager", "usermgt", "�û�������");
INSERT INTO gl_user_apps VALUES("manager", "datamgt", "���ݹ�����");
INSERT INTO gl_user_apps VALUES("manager", "servermgt", "���������");
INSERT INTO gl_user_apps VALUES("user1", "usermgt", "�û�������");
INSERT INTO gl_user_apps VALUES("user2", "datamgt", "���ݹ�����");


#
# Table structure for table 'gl_users'
#

CREATE TABLE gl_users (
  node varchar(64) NOT NULL default '',
  uid varchar(64) NOT NULL default '',
  pwd varchar(64) NOT NULL default '',
  description varchar(254) default NULL,
  certDN varchar(128) default NULL,
  keypass varchar(64) default NULL,
  role varchar(128) default NULL,
  PRIMARY KEY  (uid)
) TYPE=MyISAM;



#
# Dumping data for table 'gl_users'
#

INSERT INTO gl_users VALUES("spp", "user01", "cn=user1, ou=r&d, o=nordsan, l=beijing, st=beijing, c=cn", "�߼�", "sppix", "", "role01");
INSERT INTO gl_users VALUES("spp", "user02", "cn=user2, ou=r&d, o=nordsan, l=beijing, st=beijing, c=cn", "����", "sppix", "", "role02");
INSERT INTO gl_users VALUES("spp", "manager", "cn=manager, ou=r&d, o=nordsan, l=beijing, st=beijing, c=cn", "����Ա", "binggang li", "", "mgt");
INSERT INTO gl_users VALUES("", "user1", "user1", "�û�һ", "cn=user1, ou=r&d, o=nordsan, l=beijing, st=beijing, c=cn", "", "role1");
INSERT INTO gl_users VALUES("", "user2", "user2", "�û���", "cn=user2, ou=r&d, o=nordsan, l=beijing, st=beijing, c=cn", "", "role2");
INSERT INTO gl_users VALUES("0", "", "", NULL, NULL, "0", NULL);
INSERT INTO gl_users VALUES("", "mgt", "", "1", NULL, NULL, NULL);
INSERT INTO gl_users VALUES("", "role02", "", "0", NULL, NULL, NULL);
INSERT INTO gl_users VALUES("", "role01", "", "1", NULL, NULL, NULL);
INSERT INTO gl_users VALUES("", "role0", "", "1", NULL, NULL, NULL);
INSERT INTO gl_users VALUES("", "role1", "", "0", NULL, NULL, NULL);
INSERT INTO gl_users VALUES("", "role2", "", "0", NULL, NULL, NULL);
