//
//  ZepView.m
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Geometry/Point2D.h"
#include "Zep/Math/Vector2.h"
#include "Zep/Screen.h"
#include "Zep/Input/TouchSurface.h"
#include "Zep-iOS/TouchIDHelper.h"
#import "Zep-iOS/View.h"

@interface ZepView()
- (float)pointsToPixels:(float)points;
- (Zep::Point2D)UITouchToZepPoint:(UITouch*)touch;
@end

@implementation ZepView

- (id)initWithZepScreen:(Zep::Screen&)screen ZepTouchSurface:(Zep::TouchSurface&)touchSurface
{
    self = [self initWithFrame:[UIScreen mainScreen].bounds];
    
    if(self) {
        touchIDHelper = new Zep::TouchIDHelper();
        zepScreen = &screen;
        zepTouchSurface = &touchSurface;
        
        self.contentScaleFactor = [[UIScreen mainScreen] scale];
        [self setupLayer];
        [self setupContext];
        [self setupFrameBuffer];
        glGenRenderbuffers(1, &colorRenderbufferHandle);
        glGenRenderbuffers(1, &depthRenderbufferHandle);
    }
    
    return self;
}

- (void)setupLayer
{
    self.layer.opaque = YES;
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
    
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
}

- (void)setupContext
{
    context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    [EAGLContext setCurrentContext:context];
}

- (void)setupFrameBuffer
{
    GLuint framebufferHandle;
    glGenFramebuffers(1, &framebufferHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferHandle);
}

- (void)layoutSubviews
{
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbufferHandle);
    [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbufferHandle);
    
    float width = [self pointsToPixels:self.bounds.size.width];
    float height = [self pointsToPixels:self.bounds.size.height];
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbufferHandle);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbufferHandle);
    
    Zep::Vector2 resolution(width, height);
    zepScreen->setResolution(resolution);
}

- (void)present
{
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbufferHandle);
    [context presentRenderbuffer:GL_RENDERBUFFER];
    
}

- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent *)event
{
    for(UITouch *touch in touches) {
        int id = touchIDHelper->createID((intptr_t)touch);
        Zep::Point2D position = [self UITouchToZepPoint:touch];
        zepTouchSurface->registerTouch(id, position);
    }
}

- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent *)event
{
    for(UITouch *touch in touches) {
        int id = touchIDHelper->getID(intptr_t(touch));
        Zep::Point2D position = [self UITouchToZepPoint:touch];
        zepTouchSurface->updateTouch(id, position);
    }
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent *)event
{
    for(UITouch *touch in touches) {
        intptr_t touchAddress = intptr_t(touch);
        int id = touchIDHelper->getID(touchAddress);
        touchIDHelper->destroyID(touchAddress);
        
        Zep::Point2D position = [self UITouchToZepPoint:touch];
        zepTouchSurface->endTouch(id, position);
    }
}

- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
    for(UITouch *touch in touches) {
        intptr_t touchAddress = intptr_t(touch);
        int id = touchIDHelper->getID(touchAddress);
        touchIDHelper->destroyID(touchAddress);
        
        Zep::Point2D position = [self UITouchToZepPoint:touch];
        zepTouchSurface->cancelTouch(id, position);
    }
}

- (Zep::Point2D)UITouchToZepPoint:(UITouch*)touch {
    CGPoint iOSpoint = [touch locationInView:self];
    Zep::Point2D position;
    position[0] = [self pointsToPixels:iOSpoint.x/self.layer.bounds.size.width]*2-1;
    position[1] = [self pointsToPixels:iOSpoint.y/self.layer.bounds.size.height]*-2+1;
    return position;
}

- (float)pointsToPixels:(float)points
{
    return [[UIScreen mainScreen] scale] * points;
}

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (void)dealloc
{
    delete touchIDHelper;
}

@end
