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
    [view setMultipleTouchEnabled:true];
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
    if (!_esContext.bInitalize)
    {
        [self setupGL];
        _esContext.width = view.drawableWidth;
        _esContext.height = view.drawableHeight;
        
        _gi.Init(&_esContext);
        
        self.preferredFramesPerSecond = _esContext.fps;
        
        _esContext.bInitalize = true;
    }
    
    if ( _esContext.drawFunc )
    {
        _esContext.drawFunc();
    }
    
    //[self.context presentRenderbuffer:GL_RENDERBUFFER];
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    UITouch *touch=[touches anyObject];
    NSSet *allTouches = [event allTouches];
    int i = 0;
    if (_esContext.touchFunc)
    {
        for (UITouch *touch in touches){
            float dx = [touch locationInView:[touch view]].x;
            float dy = [touch locationInView:[touch view]].y;
            _esContext.touchFunc(i, dx, dy, allTouches.count);
            ++i;
        }
    }

}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
    //取得一个触摸对象（对于多点触摸可能有多个对象）
    UITouch *touch=[touches anyObject];

    if (_esContext.touchMoveFunc)
    {
        NSSet *allTouches = [event allTouches];
        int i = 0;
        for (UITouch *touch in touches){
            //取得当前位置
            CGPoint current=[touch locationInView:self.view];
            //取得前一个位置
            CGPoint previous=[touch previousLocationInView:self.view];
            _esContext.touchMoveFunc(i, current.x - previous.x, current.y - previous.y , allTouches.count);
            ++i;
        }

    }
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{

}

@end
