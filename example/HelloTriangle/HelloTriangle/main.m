//
//  main.m
//  HelloTriangle
//
//  Created by xuyajie on 2020/31/22.
//  Copyright © 2020 xyj. All rights reserved.
//jack19890427

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

int main(int argc, char * argv[]) {
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
    return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
