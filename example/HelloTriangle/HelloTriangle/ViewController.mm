//
//  ViewController.m
//  HelloTriangle
//
//  Created by xuyajie on 2020/3/22.
//  Copyright © 2020 xyj. All rights reserved.
//

#import "ViewController.h"
#import "SRenderContext.h"

extern void esMain( magic::SRenderContext *esContext );


@interface ViewController ()
{
    
    magic::SRenderContext _esContext;
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
        esMain( &_esContext );
        _esContext.bInitalize = true;
    }
    if ( _esContext.drawFunc )
    {
        _esContext.drawFunc( &_esContext );
    }
}


@end
