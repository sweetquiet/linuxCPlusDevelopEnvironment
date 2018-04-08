//
//  SQL.h
//  Mysql_Redis
//
//  Created by admindyn on 2018/3/16.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef SQL_h
#define SQL_h
char* sql = "select `a`.`deveui` AS `deveui`,`a`.`classmode` AS `classmode`,`a`.`place_holder` AS `place_holder`,`a`.`place_holder2` AS `place_holder2`,`a`.`appeui` AS `appeui`,`a`.`appkey` AS `appkey`,`a`.`appskey` AS `appskey`,`a`.`nwkskey` AS `nwkskey`,`a`.`devnonce` AS `devnonce`,`a`.`netid` AS `netid`,`a`.`place_holder1` AS `place_holder1`,`a`.`rx1droffset` AS `rx1droffset`,`a`.`rx2dr` AS `rx2dr`,`a`.`rxdelay` AS `rxdelay`,`a`.`rx2_freq` AS `rx2_freq`,`a`.`down_seqnum` AS `down_seqnum`,`a`.`up_seqnum` AS `up_seqnum`,`a`.`systime` AS `systime`,`a`.`datr` AS `datr`,`a`.`codr` AS `codr`,`a`.`standard` AS `standard`,`a`.`devaddr` AS `devaddr`,`a`.`appnonce` AS `appnonce`,`n`.`deveui` AS `ndeveui`,`n`.`classmode` AS `nclassmode`,`n`.`place_holder` AS `nplace_holder`,`n`.`place_holder2` AS `nplace_holder2`,`n`.`appeui` AS `nappeui`,`n`.`nwkskey` AS `nnwkskey`,`n`.`devnonce` AS `ndevnonce`,`n`.`netid` AS `nnetid`,`n`.`rx1droffset` AS `nrx1droffset`,`n`.`rx2dr` AS `nrx2dr`,`n`.`rxdelay` AS `nrxdelay`,`n`.`rx2_freq` AS `nrx2_freq`,`n`.`standard` AS `nstandard`,`n`.`devaddr` AS `ndevaddr`,`n`.`rxdelay_join` AS `rxdelay_join` from (`AS_MOTE_INFO` `a` left join `NS_MOTE_INFO` `n` on((`a`.`deveui` = `n`.`deveui`)))";

char* sqlIsNull = "select `a`.`deveui` AS `deveui`,`a`.`classmode` AS `classmode`,`a`.`place_holder` AS `place_holder`,`a`.`place_holder2` AS `place_holder2`,`a`.`appeui` AS `appeui`,`a`.`appkey` AS `appkey`,`a`.`appskey` AS `appskey`,`a`.`nwkskey` AS `nwkskey`,`a`.`devnonce` AS `devnonce`,`a`.`netid` AS `netid`,`a`.`place_holder1` AS `place_holder1`,`a`.`rx1droffset` AS `rx1droffset`,`a`.`rx2dr` AS `rx2dr`,`a`.`rxdelay` AS `rxdelay`,`a`.`rx2_freq` AS `rx2_freq`,`a`.`down_seqnum` AS `down_seqnum`,`a`.`up_seqnum` AS `up_seqnum`,`a`.`systime` AS `systime`,`a`.`datr` AS `datr`,`a`.`codr` AS `codr`,`a`.`standard` AS `standard`,`a`.`devaddr` AS `devaddr`,`a`.`appnonce` AS `appnonce`,`n`.`deveui` AS `ndeveui`,`n`.`classmode` AS `nclassmode`,`n`.`place_holder` AS `nplace_holder`,`n`.`place_holder2` AS `nplace_holder2`,`n`.`appeui` AS `nappeui`,`n`.`nwkskey` AS `nnwkskey`,`n`.`devnonce` AS `ndevnonce`,`n`.`netid` AS `nnetid`,`n`.`rx1droffset` AS `nrx1droffset`,`n`.`rx2dr` AS `nrx2dr`,`n`.`rxdelay` AS `nrxdelay`,`n`.`rx2_freq` AS `nrx2_freq`,`n`.`standard` AS `nstandard`,`n`.`devaddr` AS `ndevaddr`,`n`.`rxdelay_join` AS `rxdelay_join` from (`AS_MOTE_INFO` `a` left join `NS_MOTE_INFO` `n` on((`a`.`deveui` = `n`.`deveui`))) where n.deveui is null";

#endif /* SQL_h */
