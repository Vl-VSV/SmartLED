import os
import uvicorn
from fastapi import FastAPI
from routes import control_routes, change_values_routes, color_routes

app = FastAPI(title="Smart LED", version="0.1.0")

app.include_router(control_routes.router, tags=["control"])
app.include_router(change_values_routes.router, prefix="/changeValue", tags=["change values"])
app.include_router(color_routes.router, prefix='/color', tags=["change color"])

if __name__ == '__main__':
    uvicorn.run(app, host="0.0.0.0", port=int(os.getenv("PORT", "8080")), log_config=None)
