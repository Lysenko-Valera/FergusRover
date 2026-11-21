from pathlib import Path

from pydantic_settings import BaseSettings, SettingsConfigDict


# Resolve the project root directory.
PROJECT_ROOT = Path(__file__).resolve().parents[3]


class Settings(BaseSettings):
    """Application configuration loaded from environment variables."""

    POSTGRES_DB: str = "rover_db"
    POSTGRES_USER: str = "rover_user"
    POSTGRES_PASSWORD: str

    POSTGRES_HOST: str = "localhost"
    POSTGRES_PORT: int = 5432

    model_config = SettingsConfigDict(
        env_file=PROJECT_ROOT / ".env",
        env_file_encoding="utf-8",
        extra="ignore",
    )


settings = Settings()