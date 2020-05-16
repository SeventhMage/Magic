//
//  AppDelegate.h
//  gi
//
//  Created by xuyajie on 2020/5/16.
//  Copyright © 2020 xyj. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (readonly, strong) NSPersistentCloudKitContainer *persistentContainer;

- (void)saveContext;


@end

