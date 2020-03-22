//
//  AppDelegate.h
//  HelloTriangle
//
//  Created by xuyajie on 2020/3/22.
//  Copyright © 2020 xyj. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (readonly, strong) NSPersistentContainer *persistentContainer;

- (void)saveContext;


@end

