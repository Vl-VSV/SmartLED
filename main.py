from fastapi import FastAPI
from routes import control_routes, change_values_routes, color_routes
import uvicorn

app = FastAPI(title="Smart LED", version="0.1.0")

app.include_router(control_routes.router, tags=["control"])
app.include_router(change_values_routes.router, prefix="/changeValue", tags=["change values"])
app.include_router(color_routes.router, prefix='/color', tags=["change color"])

uvicorn.run(app)