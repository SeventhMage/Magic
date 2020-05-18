//
//  ViewController.m
//  gi
//
//  Created by xuyajie on 2020/5/16.
//  Copyright © 2020 xyj. All rights reserved.
//

//
//  ViewController.m
//  HelloTriangle
//
//  Created by xuyajie on 2020/3/22.
//  Copyright © 2020 xyj. All rights reserved.
//

#import "ViewController.h"
#import "SRenderContext.h"

#import "CGI.h"

@interface ViewController ()
{
    magic::SRenderContext _esContext;
    magic::CGI _gi;
}
@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];

    if (!self.context)
    {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
}

- (void)dealloc
{
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    memset( &_esContext, 0, sizeof( _esContext ) );
    
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];

    if ( _esContext.shutdownFunc )
    {
        _esContext.shutdownFunc();
    }
}


- (void)update
{
    if (!_esContext.bInitalize) return;
    if ( _esContext.updateFunc )
    {
        _esContext.updateFunc( );
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    _esContext.width = view.drawableWidth;
    _esContext.height = view.drawableHeight;
    if (!_esContext.bInitalize)
    {
        _gi.Init(&_esContext);
        _esContext.bInitalize = true;
    }
    
    if ( _esContext.drawFunc )
    {
        _esContext.drawFunc();
    }
}


@end