#ifndef ZOOM_SYSTEM_H
#define ZOOM_SYSTEM_H

typedef enum {
    ZOOM_IDLE,
    ZOOM_IN,
    ZOOMED,
    ZOOM_OUT
} ZoomState;

typedef struct {
    Texture2D texMain;
    Texture2D texDetail;

    Texture2D currentTex;

    float zoom;        // 1.0 → normal
    float targetZoom;  // 1.0 atau 2.0

    bool switched;

    ZoomState state;

    Rectangle backButton;
} ZoomSystem;

void InitZoomSystem(ZoomSystem *z, Texture2D mainTex);
void TriggerZoom(ZoomSystem *z, Texture2D detailTex);
void UpdateZoomSystem(ZoomSystem *z);
void DrawZoomSystem(ZoomSystem *z);

#endif