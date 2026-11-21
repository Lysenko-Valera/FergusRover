from fastapi import FastAPI

from app.api.routes.api.health import router as health_router


app = FastAPI(
    title="Rover_WEB API",
    description="Backend API for the Rover_WEB control system.",
    version="0.1.0",
)

app.include_router(health_router)





